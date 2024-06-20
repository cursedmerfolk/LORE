#pragma once

#include <algorithm>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "Player.h"

namespace Lorcana
{

class TurnAction
{
public:
    enum Type
    {
        PlayCard,
        ChallengeCard,
        InkCard,
        QuestCard,
        UseAbility,
        PassTurn
    };

    Type type;
    Player sourcePlayer;
    Card sourceCard;
    Player targetPlayer;
    Card targetCard;
    std::vector<Card> singers;
    std::string abilityName;
};

enum Phase
{
    Ready,
    Set,
    Draw,
    Main,
};

class Game
{
public:
    Player currentPlayer;
    Phase currentPhase = Phase::Ready;
    std::vector<Card> cards;
    // std::vector<std::function<void>> bag;
    std::vector<Player> players;
    std::unordered_map<std::string, std::function<bool(TurnAction&)>> abilities;

    Game() = default;
    ~Game() = default;
    Game(const Game& other) = default;

    Game(const std::vector<std::string>& playerNames);

    bool Perform(TurnAction& turnAction);

    static bool Elsa_SnowQueen_Freeze(TurnAction& turnAction);

private:
    bool PlayCard(Player& sourcePlayer, Card& sourceCard);
    bool UseAbility(Card& sourceCard, const std::string& abilityName,
                    TurnAction& turnAction);
    bool ChallengeCard(Player& sourcePlayer, Card& sourceCard,
                       Player& targetPlayer, Card& targetCard);
    bool InkCard(Player& sourcePlayer, Card& sourceCard);
    bool QuestCard(Player& sourcePlayer, Card& sourceCard);
    bool PassTurn(Player& sourcePlayer);

    // bool ResolveAbility(std::function<void>); // Resolve an ability in the bag.
};
}  // namespace Lorcana