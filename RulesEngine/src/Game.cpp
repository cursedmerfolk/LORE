#include "Game.h"

namespace Redacted
{

Game::Game(unsigned int seed) : generator(seed)
{
    if (!loadCardJson("RulesEngine/allCards.json"))
    {
        return;
    }

    // Register abilities in lookup map.
    abilities["elsa_snowqueen_freeze"] = Game::Elsa_SnowQueen_Freeze;
}

Player* Game::AddPlayer(std::string playerName)
{
    for (Player& player : players)
    {
        if (player.name == playerName)
        {
            // TODO: add logging.
            // log("[Game::AddPlayer] Player name %s already exists.", playerName);
            return nullptr;
        }
    }

    players.emplace_back(playerName);
    return nullptr;
    // return &players.at(players.size());  // <-- problem line
}

bool Game::StartGame()
{
    // Don't start the game if it's already started.
    if (currentPhase != Game::Phase::Unstarted)
    {
        return false;
    }

    // Number from 1 to N cards.
    std::vector<int> indices;
    for (int i = 1; i <= cards.size(); ++i)
    {
        indices.push_back(i);
    }

    // Each player draws 7 cards.
    for (Player& player : players)
    {
        // Make random decks for now.
        std::shuffle(indices.begin(), indices.end(), generator);
        for (int i = 1; i <= 60; ++i)
        {
            // Copy constructor called here.
            Card card = cards.at(indices.at(i));
            card.owner = &player;
            player.deck.push_back(card);
        }

        // Draw 7.
        player.DrawCards(7);
    }

    // Randomly select the current player.
    std::uniform_int_distribution<> distr(0, players.size() - 1);
    int random_number = distr(generator);
    currentPlayer = &players.at(random_number);

    currentPhase = Game::Phase::Mulligan;

    return true;
}

bool Game::loadCardJson(const std::string& fileName)
{
    // Load all cards.
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string jsonData = buffer.str();

    Json::CharReaderBuilder readerBuilder;
    Json::Value root;
    std::string errs;

    if (!Json::parseFromStream(readerBuilder, buffer, &root, &errs))
    {
        std::cerr << "Error parsing JSON: " << errs << std::endl;
        return false;
    }

    for (const Json::Value& jsonValue : root["cards"])
    {
        try
        {
            cards.emplace_back(jsonValue);
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error parsing card: " << e.what() << std::endl;
        }
    }

    return true;
}

// Json::Value Game::GetCurrentState()
// {
//     // Not sure what this is going to look like
// }

bool Game::Perform(TurnAction& turnAction)
{
    Player sourcePlayer = *turnAction.sourcePlayer;

    if (currentPhase == Game::Phase::Mulligan)
    {
        if (turnAction.type != TurnAction::Type::Mulligan)
        {
            return false;
        }

        std::vector<uint8_t> mulligans = *turnAction.mulligans;
        std::sort(mulligans.rbegin(), mulligans.rend());  // Descending order.

        for (const uint8_t& cardIndex : mulligans)
        {
            if (cardIndex < 0 || cardIndex >= sourcePlayer.hand.size())
            {
                return false;
            }

            Card card = sourcePlayer.hand.at(cardIndex);
            card.ChangeZone(sourcePlayer.hand, sourcePlayer.deck, 0);
        }

        // Draw that many cards.
        sourcePlayer.DrawCards(mulligans.size());
        sourcePlayer.doneMulligan = true;

        // Go to next phase if all players have finished their Mulligan.
        std::vector<Player> notDone = filterBy(players, &Player::doneMulligan, false);
        if (notDone.empty())
        {
            currentPlayer->DoTurnStart(false);
            currentPhase = Game::Phase::Main;
        }

        return true;
    }

    if (sourcePlayer.id != currentPlayer->id)
    {
        return false;
    }

    if (currentPhase != Game::Phase::Main)
    {
        return false;
    }

    std::cout << "Performing Turn Action: " << turnAction.getTypeString() << std::endl;

    switch (turnAction.type)
    {
        case TurnAction::Type::PlayCard:
            return PlayCard(sourcePlayer, *turnAction.sourceCard, turnAction.shiftTarget, turnAction.targetIndex);
        case TurnAction::Type::UseAbility:
            return UseAbility(*turnAction.sourceCard, *turnAction.abilityName, turnAction);
        case TurnAction::Type::ChallengeCard:
            return ChallengeCard(sourcePlayer, *turnAction.sourceCard, *turnAction.targetPlayer, *turnAction.targetCard);
        case TurnAction::Type::InkCard:
            return InkCard(sourcePlayer, *turnAction.sourceCard);
        case TurnAction::Type::QuestCard:
            return QuestCard(sourcePlayer, *turnAction.sourceCard);
        case TurnAction::Type::PassTurn:
            return PassTurn(sourcePlayer);
        case TurnAction::Type::MoveToLocation:
            return MoveToLocation(sourcePlayer, *turnAction.sourceCard, *turnAction.targetCard);
        default:
            return false;
    }
}

bool Game::PlayCard(Player& sourcePlayer, Card& sourceCard, Card* shiftTarget, int8_t targetIndex)
{
    if (!sourcePlayer.CanPlay(sourceCard))
    {
        return false;
    }

    // Exert cards in inkwell equal to card cost.
    uint8_t numExerted = 0;
    uint8_t cardCost = sourceCard.cost;
    if (shiftTarget)
    {
        cardCost = sourceCard.shiftValue;
    }

    for (auto& inkedCard : sourcePlayer.inkwell)
    {
        if (!inkedCard.isReady)
        {
            continue;
        }
        
        inkedCard.isReady = false;
        numExerted += 1;
        if (numExerted >= cardCost)
        {
            break;
        }
    }

    // Move the card to the field or discard at the desired index.
    std::vector<Card> toZone;

    if (sourceCard.cardType == CardType::Action)
    {
        toZone = sourcePlayer.discard;
    }
    else
    {
        toZone = sourcePlayer.field;
    }

    uint8_t toIndex = toZone.size();

    if (targetIndex >= 0)
    {
        toIndex = targetIndex;
    }

    sourceCard.ChangeZone(sourcePlayer.hand, toZone, toIndex);

    // TODO: ETB effects
    // Add that effect to the bag since it's a triggered ability (I think).
    // There likely needs to be a step that says 'if there's only one Ability in the bag, perform it without waiting'
    // Probably need Ability (type=Triggered, sourcePlayer, bool Perform())

    // TODO: shift targets somehow need to be kept track of

    return true;
}

bool Game::UseAbility(Card& sourceCard, const std::string& abilityName, TurnAction& turnAction)
{
    std::string lookupKey = sourceCard.baseName + "_" + sourceCard.version + "_" + abilityName;
    if (abilities.count(lookupKey))
    {
        abilities[lookupKey](turnAction);
        return true;
    }
    return false;
}

bool Game::ChallengeCard(Player& sourcePlayer, Card& sourceCard, Player& targetPlayer, Card& targetCard)
{
    if (!CanChallengeTarget(sourcePlayer, sourceCard, targetPlayer, targetCard))
    {
        return false;
    }

    sourceCard.isReady = false;
    sourceCard.ApplyDamage(targetCard.strength);
    targetCard.ApplyDamage(sourceCard.strength);

    if (sourceCard.damageCounters >= sourceCard.willpower)
    {
        sourceCard.ChangeZone(sourcePlayer.field, sourcePlayer.discard);
    }

    if (targetCard.damageCounters >= targetCard.willpower)
    {
        targetCard.ChangeZone(targetPlayer.field, targetPlayer.discard);
    }

    return true;
}

bool Game::InkCard(Player& sourcePlayer, Card& sourceCard)
{
    if (!sourcePlayer.CanInk(sourceCard))
    {
        return false;
    }

    sourceCard.ChangeZone(sourcePlayer.hand, sourcePlayer.inkwell);

    sourcePlayer.inkedThisTurn = true;

    return true;
}

bool Game::QuestCard(Player& sourcePlayer, Card& sourceCard)
{
    if (!CanQuest(sourcePlayer, sourceCard))
    {
        return false;        
    }

    sourceCard.isReady = false;
    sourcePlayer.loreTotal += sourceCard.lore;

    return true;
}

bool Game::PassTurn(Player& sourcePlayer)
{
    currentPlayer->DoTurnEnd();

    // Find player by ID.
    auto it = std::find_if(players.begin(), players.end(), [&sourcePlayer](const Player& player)
                           { return player.id == sourcePlayer.id; });
    int playerIndex = std::distance(players.begin(), it);
    int nextIndex = (playerIndex + 1) % players.size();
    currentPlayer = &players.at(nextIndex);

    currentPlayer->DoTurnStart();
    currentPhase = Game::Phase::Main;

    std::cout << "Current player: " << currentPlayer->name << std::endl;

    return true;
}


bool Game::MoveToLocation(Player& sourcePlayer, Card& sourceCard, Card& targetCard)
{
    if (!sourcePlayer.CanMove(sourceCard, targetCard))
    {
        return false;
    }

    // Exert cards in inkwell equal to location's move cost.
    uint8_t numExerted = 0;
    for (auto& inkedCard : sourcePlayer.inkwell)
    {
        if (!inkedCard.isReady)
        {
            continue;
        }
        
        inkedCard.isReady = false;
        numExerted += 1;
        if (numExerted >= targetCard.moveCost)
        {
            break;
        }
    }

    // Move character to location.
    sourceCard.atLocation = &targetCard;

    return true;
}

bool Game::CanChallenge(Player& sourcePlayer, Card& sourceCard)
{
    // Characters can't attack unless they're Ready.
    if (!sourceCard.isReady)
    {
        return false;
    }

    // Characters can't attack unless they're Dry or have Rush.
    if (!sourceCard.isDry && !sourceCard.hasRush)
    {
        return false;
    }

    // Only characters can challenge.
    if (sourceCard.cardType != CardType::Character)
    {
        return false;
    }

    return true;
}

bool Game::CanChallengeTarget(Player& sourcePlayer, Card& sourceCard, Player& targetPlayer, Card& targetCard)
{

    if (!CanChallenge(sourcePlayer, sourceCard))
    {
        return false;
    }

    // Characters can't challenge friendly characters.
    if (&sourcePlayer == &targetPlayer)
    {
        return false;
    }

    // Only characters and locations can be challenged.
    if (targetCard.cardType != CardType::Character && targetCard.cardType != CardType::Location)
    {
        return false;
    }

    // If the targetPlayer has one or more challenge-able bodyGuards, they must be challenged first.
    const auto& bodyGuards = filterBy(targetPlayer.field, &Card::hasBodyguard, true);

    // TODO: untested
    if (!bodyGuards.empty() && !containsInstance(bodyGuards, targetCard))
    {
        return false;
    }

    // If the target is Evasive, this card must also have Evasive to challenge it.    
    if (targetCard.hasEvasive && !sourceCard.hasEvasive)
    {
        return false;
    }

    return true;
}

bool Game::CanChoose(Player& sourcePlayer, Card& sourceCard, Player& targetPlayer, Card& targetCard)
{
    // Currently a player can always target their own cards.
    if (&sourcePlayer == &targetPlayer)
    {
        return true;
    }

    // Cards with Ward can't be chosen.
    if (targetCard.hasWard)
    {
        return false;
    }

    return true;
}

bool Game::CanQuest(Player& sourcePlayer, Card& sourceCard)
{
    // Used by Isabella Madrigal
    if (!sourceCard.canQuestThisTurn)
    {
        return false;
    }

    if (sourceCard.cardType != CardType::Character || !sourceCard.isReady || !sourceCard.isDry)
    {
        return false;
    }

    return true;
}

bool Game::Elsa_SnowQueen_Freeze(TurnAction& turnAction)
{
    Card sourceCard = *turnAction.sourceCard;
    Card targetCard = *turnAction.targetCard;

    if (!sourceCard.isReady)
    {
        return false;
    }

    // Exert this card.
    sourceCard.isReady = false;

    // Exert the chosen card.
    targetCard.isReady = false;

    return true;
}

}  // namespace Redacted
