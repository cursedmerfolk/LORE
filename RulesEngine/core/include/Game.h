#pragma once

#include <algorithm>
#include <ctime>
#include <iostream>
#include <functional>
#include <fstream>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

#include "Player.h"
#include "Util.h"

namespace Lorcana
{

// TODO/Note: this may just get turned into a Json::Value at some point.
class TurnAction
{
public:
    enum Type
    {
        Mulligan,
        PlayCard,
        ChallengeCard,
        InkCard,
        QuestCard,
        UseAbility,
        PassTurn
    };

    Type type;
    // Pointers feel wrong, not sure how to fix.
    Player* sourcePlayer;
    Card* sourceCard;
    Player* targetPlayer;
    Card* targetCard;
    std::vector<Card>* singers;
    std::string* abilityName;
    std::vector<uint8_t>* mulligans;
};

enum Phase
{
    Mulligan,
    Ready,
    Set,
    Draw,
    Main,
};

class Game
{
public:
    Player* currentPlayer;
    Phase currentPhase = Phase::Mulligan;
    std::vector<Card> cards;
    // std::vector<std::function<void>> bag;
    std::vector<Player> players;
    std::unordered_map<std::string, std::function<bool(TurnAction&)>> abilities;

    Game() = default;
    ~Game() = default;
    Game(const Game& other) = default;

    Game(const std::vector<std::string>& playerNames, unsigned int seed = unsigned(std::time(0)));

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

    bool loadCardJson(const std::string& fileName);

    // bool ResolveAbility(std::function<void>); // Resolve an ability in the bag.
};
}  // namespace Lorcana