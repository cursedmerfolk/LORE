#pragma once

#include "Card.h"
#include "Player.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /*
     * 
     */

    //const char* player1, const char* player2, 

    void* Game_Create();
    void* Game_Create_Seeded(unsigned int seed);
    void Game_Destroy(void* gamePtr);

    bool PlayCard(void* gamePtr, Redacted::Player& sourcePlayer, Redacted::Card& sourceCard);
    bool ChallengeCard(void* gamePtr, const char* playerName1, int cardIndex1, const char* playerName2, int cardIndex2);
    bool InkCard(void* gamePtr, const char* playerName, int cardIndex);
    bool QuestCard(void* gamePtr, const char* playerName, int cardIndex);
    bool Mulligan(void* gamePtr, const char* playerName, int* cardIndices, int arrayLength);
    bool PassTurn(void* gamePtr, const char* playerName);
    bool MoveToLocation(void* gamePtr, const char* playerName, int cardIndex, int locationIndex);

    // Used by UIs to signify actions that are / aren't allowed.
    bool CanPlay(void* gamePtr, const char* playerName, int cardIndex);  // TODO: untested
    bool CanInk(void* gamePtr, const char* playerName, int cardIndex);  // TODO: untested
    bool CanChallenge(void* gamePtr, const char* playerName, int cardIndex);  // TODO: untested
    bool CanChallengeTarget(void* gamePtr, const char* playerName1, int cardIndex1, const char* playerName2, int cardIndex2);  // TODO: untested
    bool CanChoose(void* gamePtr, const char* playerName1, int cardIndex1, const char* playerName2, int cardIndex2);  // TODO: untested
    bool CanQuest(void* gamePtr, const char* playerName, int cardIndex);  // TODO: untested
    bool CanMove(void* gamePtr, const char* playerName, int cardIndex, int locationIndex);  // TODO: untested

#ifdef __cplusplus
}
#endif