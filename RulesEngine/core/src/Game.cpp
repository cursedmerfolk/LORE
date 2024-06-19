#include <iostream>
#include <fstream>

#include "Game.h"

namespace Lorcana {

    Game::Game(const std::vector<std::string>& playerNames) {
        for (const auto& name : playerNames) {
            players[name] = Player(name);
        }

        // Register abilities in lookup map.
        abilities["elsa_snowqueen_freeze"] = Game::Elsa_SnowQueen_Freeze;

        // Load all cards.
        std::ifstream file("allCards.json");
        if (!file.is_open()) {
            std::cerr << "Error opening file" << std::endl;
            return;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string jsonData = buffer.str();

        Json::CharReaderBuilder readerBuilder;
        Json::Value root;
        std::string errs;

        if (!Json::parseFromStream(readerBuilder, buffer, &root, &errs)) {
            std::cerr << "Error parsing JSON: " << errs << std::endl;
            return;
        }

        for (const auto& jsonValue : root["cards"]) {
            try {
                cards.emplace_back(jsonValue);
            } catch (const std::exception& e) {
                std::cerr << "Error parsing card: " << e.what() << std::endl;
            }
        }
    }

    bool Game::Perform(TurnAction& turnAction) {
        std::cout << "Performing Turn Action: " << static_cast<int>(turnAction.type) << std::endl;

        switch (turnAction.type) {
            case TurnAction::Type::PlayCard:
                return PlayCard(turnAction.sourcePlayer, turnAction.sourceCard);
            case TurnAction::Type::UseAbility:
                return UseAbility(turnAction.sourceCard, turnAction.abilityName, turnAction);
            case TurnAction::Type::ChallengeCard:
                return ChallengeCard(turnAction.sourcePlayer, turnAction.sourceCard, turnAction.targetPlayer, turnAction.targetCard);
            case TurnAction::Type::InkCard:
                return InkCard(turnAction.sourcePlayer, turnAction.sourceCard);
            case TurnAction::Type::QuestCard:
                return QuestCard(turnAction.sourcePlayer, turnAction.sourceCard);
            default:
                return false;
        }
    }

    bool Game::PlayCard(Player& sourcePlayer, Card& sourceCard) {
        if (!sourcePlayer.CanPlay(sourceCard)) {
            return false;
        }

        int numExerted = 0;
        for (auto& inkedCard : sourcePlayer.inkwell) {
            if (inkedCard.isReady) {
                inkedCard.isReady = false;
                numExerted += 1;
                if (numExerted >= sourceCard.cost) {
                    break;
                }
            }
        }

        // sourcePlayer.hand.erase(std::remove(sourcePlayer.hand.begin(), sourcePlayer.hand.end(), sourceCard), sourcePlayer.hand.end());
        // sourcePlayer.field.push_back(sourceCard);

        return true;
    }

    bool Game::UseAbility(Card& sourceCard, const std::string& abilityName, TurnAction& turnAction) {
        std::string lookupKey = sourceCard.name + "_" + sourceCard.version + "_" + abilityName;
        if (abilities.count(lookupKey)) {
            abilities[lookupKey](turnAction);
            return true;
        }
        return false;
    }

    bool Game::ChallengeCard(Player& sourcePlayer, Card& sourceCard, Player& targetPlayer, Card& targetCard) {
        sourceCard.isReady = false;
        sourceCard.damageCounters += targetCard.strength;
        targetCard.damageCounters += sourceCard.strength;

        if (sourceCard.damageCounters >= sourceCard.willpower) {
            // sourcePlayer.field.erase(std::remove(sourcePlayer.field.begin(), sourcePlayer.field.end(), sourceCard), sourcePlayer.field.end());
            // sourcePlayer.discard.push_back(sourceCard);
        }

        if (targetCard.damageCounters >= targetCard.willpower) {
            // targetPlayer.field.erase(std::remove(targetPlayer.field.begin(), targetPlayer.field.end(), targetCard), targetPlayer.field.end());
            // targetPlayer.discard.push_back(targetCard);
        }

        return true;
    }

    bool Game::InkCard(Player& sourcePlayer, Card& sourceCard) {
        if (!sourceCard.inkable) {
            return false;
        }

        // sourcePlayer.hand.erase(std::remove(sourcePlayer.hand.begin(), sourcePlayer.hand.end(), sourceCard), sourcePlayer.hand.end());
        // sourcePlayer.inkwell.push_back(sourceCard);

        return true;
    }

    bool Game::QuestCard(Player& sourcePlayer, Card& sourceCard) {
        if (sourceCard.cardType != CardType::Character || !sourceCard.isReady) {
            return false;
        }

        sourceCard.isReady = false;
        sourcePlayer.loreTotal += sourceCard.lore;

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
	
}
