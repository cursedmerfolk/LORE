#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    void* Game_Create(const char* player1, const char* player2);
    void* Game_Create_Seeded(const char* player1, const char* player2, unsigned int seed);
    void Game_Destroy(void* gamePtr);

    bool PlayCard(void* gamePtr, const char* playerName, int cardIndex);
    bool ChallengeCard(void* gamePtr, const char* playerName1, int cardIndex1, const char* playerName2, int cardIndex2);
    bool InkCard(void* gamePtr, const char* playerName, int cardIndex);
    bool QuestCard(void* gamePtr, const char* playerName, int cardIndex);
    bool Mulligan(void* gamePtr, const char* playerName, int* cardIndices, int arrayLength);
    bool PassTurn(void* gamePtr, const char* playerName);

#ifdef __cplusplus
}
#endif