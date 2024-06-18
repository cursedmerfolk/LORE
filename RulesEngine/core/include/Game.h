#pragma once

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include "Player.h"

namespace Lorcana {

    enum class TurnActionType {
        PlayCard,
        ChallengeCard,
        InkCard,
        QuestCard,
        UseAbility
    };

    class TurnAction {
    public:
        TurnActionType type;
        Player sourcePlayer;
        Card sourceCard;
        Player targetPlayer;
        Card targetCard;
        std::vector<Card> singers;
        std::string abilityName;
    };

    class Game {
    public:
        std::unordered_map<std::string, Player> players;

        Game(const std::vector<std::string>& playerNames);

        bool Perform(TurnAction& turnAction);
		
		static bool Elsa_SnowQueen_Freeze(TurnAction& turnAction);
		std::unordered_map<std::string, std::function<bool(TurnAction&)>> abilities;

    private:
        bool PlayCard(Player& sourcePlayer, Card& sourceCard);
        bool UseAbility(Card& sourceCard, const std::string& abilityName, TurnAction& turnAction);
        bool ChallengeCard(Player& sourcePlayer, Card& sourceCard, Player& targetPlayer, Card& targetCard);
        bool InkCard(Player& sourcePlayer, Card& sourceCard);
        bool QuestCard(Player& sourcePlayer, Card& sourceCard);
    };
}