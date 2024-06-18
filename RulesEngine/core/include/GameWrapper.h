#pragma once

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllexport) void Game_Create(void** game, const char** playerNames, int playerCount);
__declspec(dllexport) void Game_Destroy(void** game);

__declspec(dllexport) void PlayCard(void* game, const char* playerName, int cardIndex);
__declspec(dllexport) void InkCard(void* game, const char* playerName, int cardIndex);

#ifdef __cplusplus
}
#endif