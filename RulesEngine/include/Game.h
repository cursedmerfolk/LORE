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
        ChallengeCard,
        InkCard,
        Mulligan,
        PassTurn,
        PlayCard,
        QuestCard,
        UseAbility,
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
    Card* shiftTarget;

    std::string getTypeString()
    {
        if (type == Type::ChallengeCard) return "ChallengeCard";
        if (type == Type::InkCard) return "InkCard";
        if (type == Type::Mulligan) return "Mulligan";
        if (type == Type::PassTurn) return "PassTurn";
        if (type == Type::PlayCard) return "PlayCard";
        if (type == Type::QuestCard) return "QuestCard";
        if (type == Type::UseAbility) return "UseAbility";
        return "Unknown";
    }
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
    Game() = default;

    ~Game() = default;

    Game(const Game& other) = default;

    Game(const std::vector<std::string>& playerNames, unsigned int seed = unsigned(std::time(0)));

    bool Perform(TurnAction& turnAction);

    // Used by the wrapper to signify to the UI about actions that are / aren't allowed.
    bool CanChallenge(Player& sourcePlayer, Card& sourceCard);
    bool CanChallengeTarget(Player& sourcePlayer, Card& sourceCard, Player& targetPlayer, Card& targetCard);
    bool CanChoose(Player& sourcePlayer, Card& sourceCard, Player& targetPlayer, Card& targetCard);

    // Implementations of card abilities (Name_Version_AbilityName).
    static bool Elsa_SnowQueen_Freeze(TurnAction& turnAction);

    Player* currentPlayer;
    Phase currentPhase = Phase::Mulligan;
    std::vector<Card> cards;
    // std::vector<std::function<void>> bag;
    std::vector<Player> players;
    std::unordered_map<std::string, std::function<bool(TurnAction&)>> abilities;

private:
    bool PlayCard(Player& sourcePlayer, Card& sourceCard, Card* shiftTarget = nullptr);
    bool UseAbility(Card& sourceCard, const std::string& abilityName, TurnAction& turnAction);
    bool ChallengeCard(Player& sourcePlayer, Card& sourceCard, Player& targetPlayer, Card& targetCard);
    bool InkCard(Player& sourcePlayer, Card& sourceCard);
    bool QuestCard(Player& sourcePlayer, Card& sourceCard);
    bool PassTurn(Player& sourcePlayer);

    bool loadCardJson(const std::string& fileName);

    // bool ResolveAbility(std::function<void>); // Resolve an ability in the bag.
};
}  // namespace Lorcana