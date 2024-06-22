#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    void* Game_Create(const char* player1, const char* player2);
    void* Game_Create_Seed(const char* player1, const char* player2, unsigned int seed);
    void Game_Destroy(void* gamePtr);

    bool PlayCard(void* gamePtr, const char* playerName, int cardIndex);
    bool InkCard(void* gamePtr, const char* playerName, int cardIndex);
    bool QuestCard(void* gamePtr, const char* playerName, int cardIndex);
    bool Mulligan(void* gamePtr, const char* playerName, int* cardIndices, int arrayLength);
    // void PassTurn(void* game, const char* playerName);

#ifdef __cplusplus
}
#endif