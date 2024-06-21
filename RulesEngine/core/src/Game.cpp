#include "Game.h"

#include <fstream>
#include <iostream>

namespace Lorcana
{

// Generic filter function
template <typename TYPE, typename CLASS>
std::vector<CLASS> filterBy(const std::vector<CLASS>& instances, TYPE CLASS::*property, TYPE value) {
    std::vector<CLASS> found;
    for (const CLASS& instance : instances) {
        if (instance.*property == value) {
            found.push_back(instance);
        }
    }
    return found;
}

Game::Game(const std::vector<std::string>& playerNames)
{
    for (const auto& name : playerNames)
    {
        players.emplace_back(name);
    }

    currentPlayer = players.at(0);

    
    std::vector<Player> done = filterBy(players, &Player::doneMulligan, true);
    for (auto& element : done)
    {
        std::cout << element.name << std::endl;
    }
    if (done.empty())
    {
        std::cout << "hi1" << std::endl;
        currentPhase = Phase::Ready;
    }

    // Register abilities in lookup map.
    abilities["elsa_snowqueen_freeze"] = Game::Elsa_SnowQueen_Freeze;

    // Load all cards.
    std::ifstream file("../../allCards.json");
    if (!file.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return;
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
        return;
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
}

// Json::Value Game::GetCurrentState()
// {
//     // Not sure what this is going to look like
// }

bool Game::Perform(TurnAction& turnAction)
{
    Player sourcePlayer = turnAction.sourcePlayer;

    if (currentPhase == Phase::Mulligan)
    {
        std::vector<uint8_t> mulligans = turnAction.mulligans;
        std::sort(mulligans.rbegin(), mulligans.rend());  // Descending order.
        for (const uint8_t& cardIndex : mulligans)
        {
            if (cardIndex < 0 || cardIndex >= sourcePlayer.hand.size())
            {
                return false;
            }
            sourcePlayer.hand.erase(sourcePlayer.hand.begin() + cardIndex);
        }

        sourcePlayer.doneMulligan = true;

        // Go to next phase if all players have finished their Mulligan.
        std::vector<Player> done = filterBy(players, &Player::doneMulligan, true);
        if (done.empty())
        {
            currentPhase = Phase::Ready;
        }

        return true;
    }

    if (sourcePlayer.id != currentPlayer.id)
    {
        return false;
    }

    if (currentPhase != Phase::Main)
    {
        return false;
    }

    std::cout << "Performing Turn Action: " << static_cast<int>(turnAction.type) << std::endl;

    switch (turnAction.type)
    {
        case TurnAction::Type::PlayCard:
            return PlayCard(sourcePlayer, turnAction.sourceCard);
        case TurnAction::Type::UseAbility:
            return UseAbility(turnAction.sourceCard, turnAction.abilityName, turnAction);
        case TurnAction::Type::ChallengeCard:
            return ChallengeCard(sourcePlayer, turnAction.sourceCard, turnAction.targetPlayer, turnAction.targetCard);
        case TurnAction::Type::InkCard:
            return InkCard(sourcePlayer, turnAction.sourceCard);
        case TurnAction::Type::QuestCard:
            return QuestCard(sourcePlayer, turnAction.sourceCard);
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

    int numExerted = 0;
    for (auto& inkedCard : sourcePlayer.inkwell)
    {
        if (inkedCard.isReady)
        {
            inkedCard.isReady = false;
            numExerted += 1;
            if (numExerted >= sourceCard.cost)
            {
                break;
            }
        }
    }

    // sourcePlayer.hand.erase(std::remove(sourcePlayer.hand.begin(), sourcePlayer.hand.end(), sourceCard), sourcePlayer.hand.end());
    // sourcePlayer.field.push_back(sourceCard);

    return true;
}

bool Game::UseAbility(Card& sourceCard, const std::string& abilityName, TurnAction& turnAction)
{
    std::string lookupKey = sourceCard.name + "_" + sourceCard.version + "_" + abilityName;
    if (abilities.count(lookupKey))
    {
        abilities[lookupKey](turnAction);
        return true;
    }
    return false;
}

bool Game::ChallengeCard(Player& sourcePlayer, Card& sourceCard, Player& targetPlayer, Card& targetCard)
{
    sourceCard.isReady = false;
    sourceCard.damageCounters += targetCard.strength;
    targetCard.damageCounters += sourceCard.strength;

    if (sourceCard.damageCounters >= sourceCard.willpower)
    {
        // sourcePlayer.field.erase(std::remove(sourcePlayer.field.begin(), sourcePlayer.field.end(), sourceCard), sourcePlayer.field.end());
        // sourcePlayer.discard.push_back(sourceCard);
    }

    if (targetCard.damageCounters >= targetCard.willpower)
    {
        // targetPlayer.field.erase(std::remove(targetPlayer.field.begin(), targetPlayer.field.end(), targetCard), targetPlayer.field.end());
        // targetPlayer.discard.push_back(targetCard);
    }

    return true;
}

bool Game::InkCard(Player& sourcePlayer, Card& sourceCard)
{
    if (!sourceCard.inkable)
    {
        return false;
    }

    // sourcePlayer.hand.erase(std::remove(sourcePlayer.hand.begin(), sourcePlayer.hand.end(), sourceCard), sourcePlayer.hand.end());
    // sourcePlayer.inkwell.push_back(sourceCard);

    return true;
}

bool Game::QuestCard(Player& sourcePlayer, Card& sourceCard)
{
    if (sourceCard.cardType != CardType::Character || !sourceCard.isReady)
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
    currentPlayer = players.at(nextIndex);

    return true;
}

bool Game::Elsa_SnowQueen_Freeze(TurnAction& turnAction)
{
    Card& sourceCard = turnAction.sourceCard;
    Card& targetCard = turnAction.targetCard;

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
