#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    void* Game_Create(const char* player1, const char* player2);
    void Game_Destroy(void* game);

    void PlayCard(void* game, const char* playerName, int cardIndex);
    void InkCard(void* game, const char* playerName, int cardIndex);

#ifdef __cplusplus
}
#endif