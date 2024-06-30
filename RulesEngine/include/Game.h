#pragma once

#include <algorithm>
#include <ctime>
#include <iostream>
#include <functional>
#include <fstream>
#include <optional>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

#include "TurnAction.h"
#include "Player.h"
#include "Util.h"


namespace Lorcana
{

class Game
{
public:

    enum Phase
    {
        Mulligan,
        Ready,
        Set,
        Draw,
        Main,
    };

    Game() = default;

    ~Game() = default;

    Game(const Game& other) = default;

    Game(const std::vector<std::string>& playerNames, unsigned int seed = unsigned(std::time(0)));

    bool Perform(TurnAction& turnAction);

    // Used by the wrapper to signify to the UI about actions that are / aren't allowed.
    bool CanChallenge(Player& sourcePlayer, Card& sourceCard);
    bool CanChallengeTarget(Player& sourcePlayer, Card& sourceCard, Player& targetPlayer, Card& targetCard);
    bool CanChoose(Player& sourcePlayer, Card& sourceCard, Player& targetPlayer, Card& targetCard);
    bool CanQuest(Player& sourcePlayer, Card& sourceCard);  // TODO: not tested

    // Implementations of card abilities (Name_Version_AbilityName).
    static bool Elsa_SnowQueen_Freeze(TurnAction& turnAction);

    Player* currentPlayer;
    Phase currentPhase = Game::Phase::Mulligan;
    std::vector<Card> cards;
    // std::vector<std::function<void>> bag;
    std::vector<Player> players;
    std::unordered_map<std::string, std::function<bool(TurnAction&)>> abilities;

private:
    bool PlayCard(Player& sourcePlayer, Card& sourceCard, std::optional<Card>& shiftTarget);
    bool UseAbility(Card& sourceCard, const std::string& abilityName, TurnAction& turnAction);
    bool ChallengeCard(Player& sourcePlayer, Card& sourceCard, Player& targetPlayer, Card& targetCard);
    bool InkCard(Player& sourcePlayer, Card& sourceCard);
    bool QuestCard(Player& sourcePlayer, Card& sourceCard);
    bool PassTurn(Player& sourcePlayer);
    bool MoveToLocation(Player& sourcePlayer, Card& sourceCard, Card& targetCard);  // TODO: not tested

    bool loadCardJson(const std::string& fileName);

    Player getSourcePlayer(const TurnAction& turnAction)
    {
        return players.at(turnAction.sourcePlayerIndex);
    }
    Card getSourceCard(const TurnAction& turnAction)
    {
        Player sourcePlayer = getSourcePlayer(turnAction);
        std::vector<Card> sourceZone = sourcePlayer.getCardZone(turnAction);
        return sourceZone.at(turnAction.sourceCardIndex);
    }
    Player getTargetPlayer(const TurnAction& turnAction)
    {
        return players.at(turnAction.targetPlayerIndex);
    }
    Card getTargetCard(const TurnAction& turnAction)
    {
        Player targetPlayer = getSourcePlayer(turnAction);
        std::vector<Card> targetZone = targetPlayer.getCardZone(turnAction);
        return targetZone.at(turnAction.sourceCardIndex);
    }

    std::optional<Card> getShiftTarget(const TurnAction& turnAction)
    {
        if (turnAction.shiftTargetIndex > 0)
        {
            Player sourcePlayer = getSourcePlayer(turnAction);
            return sourcePlayer.field.at(turnAction.shiftTargetIndex);
        }
        return std::nullopt;
    }

    std::vector<uint8_t> getMulligans(const TurnAction& turnAction)
    {
        Player sourcePlayer = getSourcePlayer(turnAction);
        std::vector<uint8_t> mulligans;
        for (auto& cardIndex : turnAction.mulligans)
        {
            if (cardIndex == -1)
            {
                continue;
            }
            mulligans.push_back((uint8_t)cardIndex);
        }
        return mulligans;
    }

    // bool ResolveAbility(std::function<void>); // Resolve an ability in the bag.
};
}  // namespace Lorcana