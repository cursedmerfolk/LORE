#include "Game.h"

namespace Lorcana
{

Game::Game(const std::vector<std::string>& playerNames, unsigned int seed)
{
    std::mt19937 generator(seed); // Mersenne Twister random number generator

    for (const auto& name : playerNames)
    {
        players.emplace_back(name);
    }

    std::uniform_int_distribution<> distr(0, players.size() - 1);
    int random_number = distr(generator);
    currentPlayer = &players.at(random_number);

    if (!loadCardJson("../../allCards.json"))
    {
        return;
    }

    // Register abilities in lookup map.
    abilities["elsa_snowqueen_freeze"] = Game::Elsa_SnowQueen_Freeze;

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
            player.deck.push_back(cards.at(indices.at(i)));
        }

        // Draw 7.
        player.DrawCards(7);
    }

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
    Player& sourcePlayer = *turnAction.sourcePlayer;

    if (currentPhase == Phase::Mulligan)
    {
        if (turnAction.type != TurnAction::Type::Mulligan)
        {
            return false;
        }

        std::vector<uint8_t> mulligans = *turnAction.mulligans;
        std::sort(mulligans.rbegin(), mulligans.rend());  // Descending order. TODO: verify this.

        for (const uint8_t& cardIndex : mulligans)
        {
            if (cardIndex < 0 || cardIndex >= sourcePlayer.hand.size())
            {
                return false;
            }
            sourcePlayer.hand.erase(sourcePlayer.hand.begin() + cardIndex);
        }

        // Draw that many cards.
        sourcePlayer.DrawCards(mulligans.size());
        sourcePlayer.doneMulligan = true;

        // Go to next phase if all players have finished their Mulligan.
        std::vector<Player> notDone = filterBy(players, &Player::doneMulligan, false);
        if (notDone.empty())
        {
            currentPlayer->DoTurnStart(false);
            currentPhase = Phase::Main;
        }

        return true;
    }

    if (sourcePlayer.id != currentPlayer->id)
    {
        return false;
    }

    if (currentPhase != Phase::Main)
    {
        return false;
    }

    std::cout << "Performing Turn Action: " << std::to_string(turnAction.type) << std::endl;

    switch (turnAction.type)
    {
        case TurnAction::Type::PlayCard:
            return PlayCard(sourcePlayer, *turnAction.sourceCard);
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
        default:
            return false;
    }
}

bool Game::PlayCard(Player& sourcePlayer, Card& sourceCard)
{
    if (!sourcePlayer.CanPlay(sourceCard))
    {
        return false;
    }

    // Exert cards in inkwell equal to card cost.
    int numExerted = 0;
    for (auto& inkedCard : sourcePlayer.inkwell)
    {
        if (!inkedCard.isReady)
        {
            continue;
        }
        
        inkedCard.isReady = false;
        numExerted += 1;
        if (numExerted >= sourceCard.cost)
        {
            break;
        }
    }

    auto it = std::find_if(sourcePlayer.hand.begin(), sourcePlayer.hand.end(), [&sourceCard](const Card& card)
                           { return &card == &sourceCard; });

    if (sourceCard.cardType == CardType::Action)
    {
        sourcePlayer.discard.push_back(sourceCard);
    }
    else
    {
        sourcePlayer.field.push_back(sourceCard);
    }

    // TODO: ETB effects
    // Probably generic 'check game state'

    sourcePlayer.hand.erase(it);

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
    if (&sourcePlayer == &targetPlayer)
    {
        return false;
    }
    if (&sourceCard == &targetCard)
    {
        return false;
    }

    sourceCard.isReady = false;
    sourceCard.damageCounters += targetCard.strength;
    targetCard.damageCounters += sourceCard.strength;

    if (sourceCard.damageCounters >= sourceCard.willpower)
    {
        auto it = std::find_if(sourcePlayer.field.begin(), sourcePlayer.field.end(), [&sourceCard](const Card& card)
                            { return &card == &sourceCard; });

        sourcePlayer.field.erase(it);
        sourcePlayer.discard.push_back(sourceCard);
    }

    if (targetCard.damageCounters >= targetCard.willpower)
    {
        auto it = std::find_if(targetPlayer.field.begin(), targetPlayer.field.end(), [&sourceCard](const Card& card)
                            { return &card == &sourceCard; });

        targetPlayer.field.erase(it);
        targetPlayer.discard.push_back(targetCard);
    }

    return true;
}

bool Game::InkCard(Player& sourcePlayer, Card& sourceCard)
{
    if (sourcePlayer.inkedThisTurn)
    {
        return false;
    }

    if (!sourceCard.inkable)
    {
        return false;
    }

    sourcePlayer.inkwell.push_back(sourceCard);
    
    sourcePlayer.inkedThisTurn = true;

    // Get card index.
    auto it = std::find_if(sourcePlayer.hand.begin(), sourcePlayer.hand.end(), [&sourceCard](const Card& card)
                           { return &card == &sourceCard; });
    sourcePlayer.hand.erase(it);

    return true;
}

bool Game::QuestCard(Player& sourcePlayer, Card& sourceCard)
{
    if (sourceCard.cardType != CardType::Character || !sourceCard.isReady || !sourceCard.isDry)
    {
        return false;
    }

    sourceCard.isReady = false;
    sourcePlayer.loreTotal += sourceCard.lore;

    return true;
}

bool Game::PassTurn(Player& sourcePlayer)
{
    // Find player by ID.
    auto it = std::find_if(players.begin(), players.end(), [&sourcePlayer](const Player& player)
                           { return player.id == sourcePlayer.id; });
    int playerIndex = std::distance(players.begin(), it);
    int nextIndex = (playerIndex + 1) % players.size();
    currentPlayer = &players.at(nextIndex);

    return true;
}

bool Game::Elsa_SnowQueen_Freeze(TurnAction& turnAction)
{
    Card& sourceCard = *turnAction.sourceCard;
    Card& targetCard = *turnAction.targetCard;

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

}  // namespace Lorcana