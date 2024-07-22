#pragma once

#include "Card.h"
#include "Player.h"
#include "TurnAction.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /*
     * 
     */

    void* Game_Create();
    void* Game_Create_Seeded(unsigned int seed);
    void Game_Destroy(void* gamePtr);
    
    Redacted::TurnAction AddPlayer(void* gamePtr, const char* playerName);
    Redacted::TurnAction StartGame(void* gamePtr);

    Redacted::TurnAction PlayCard(void* gamePtr, Redacted::Player& sourcePlayer, Redacted::Card& sourceCard, int8_t targetIndex = -1);
    Redacted::TurnAction ChallengeCard(void* gamePtr, Redacted::Player& sourcePlayer, Redacted::Card& sourceCard, Redacted::Player& targetPlayer, Redacted::Card& targetCard); 
    Redacted::TurnAction InkCard(void* gamePtr, Redacted::Player& sourcePlayer, Redacted::Card& sourceCard);
    Redacted::TurnAction QuestCard(void* gamePtr, Redacted::Player& sourcePlayer, Redacted::Card& sourceCard);
    Redacted::TurnAction Mulligan(void* gamePtr, Redacted::Player& sourcePlayer, std::vector<uint8_t> mulligans);
    Redacted::TurnAction PassTurn(void* gamePtr, Redacted::Player& sourcePlayer);
    Redacted::TurnAction MoveToLocation(void* gamePtr, Redacted::Player& sourcePlayer, Redacted::Card& sourceCard, Redacted::Card& targetLocation);

    // TODO: fix these in GameWrapper.cpp
    // Used by UIs to signify actions that are / aren't allowed.
    // Redacted::TurnAction CanPlay(void* gamePtr, const char* playerName, int cardIndex);  // TODO: untested
    // Redacted::TurnAction CanInk(void* gamePtr, const char* playerName, int cardIndex);  // TODO: untested
    // Redacted::TurnAction CanChallenge(void* gamePtr, const char* playerName, int cardIndex);  // TODO: untested
    // Redacted::TurnAction CanChallengeTarget(void* gamePtr, const char* playerName1, int cardIndex1, const char* playerName2, int cardIndex2);  // TODO: untested
    // Redacted::TurnAction CanChoose(void* gamePtr, const char* playerName1, int cardIndex1, const char* playerName2, int cardIndex2);  // TODO: untested
    // Redacted::TurnAction CanQuest(void* gamePtr, const char* playerName, int cardIndex);  // TODO: untested
    // Redacted::TurnAction CanMove(void* gamePtr, const char* playerName, int cardIndex, int locationIndex);  // TODO: untested

#ifdef __cplusplus
}
#endif