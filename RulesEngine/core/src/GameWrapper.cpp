#include "GameWrapper.h"
#include "Game.h"

using namespace Lorcana;

extern "C" {

__declspec(dllexport) void Game_Create(void** game, const char** playerNames, int playerCount) {
    std::vector<std::string> players(playerNames, playerNames + playerCount);
    *game = new Game(players);
}

__declspec(dllexport) void Game_Destroy(void** game) {
    delete (Game*)*game;
    *game = nullptr;
}

__declspec(dllexport) void PlayCard(void* gamePtr, const char* playerName, int cardIndex)
{
    Game* game = (Game*)gamePtr;
    Player sourcePlayer = game->players[playerName];
    Card sourceCard = sourcePlayer.hand[cardIndex];
    TurnAction turnAction;
    turnAction.type = TurnAction::Type::PlayCard;
    turnAction.sourcePlayer = sourcePlayer;
    turnAction.sourceCard = sourceCard;
    game->Perform(turnAction);
}

__declspec(dllexport) void InkCard(void* gamePtr, const char* playerName, int cardIndex)
{
    Game* game = (Game*)gamePtr;
    Player sourcePlayer = game->players[playerName];
    Card sourceCard = sourcePlayer.hand[cardIndex];
    TurnAction turnAction;
    turnAction.type = TurnAction::Type::InkCard;
    turnAction.sourcePlayer = sourcePlayer;
    turnAction.sourceCard = sourceCard;
    game->Perform(turnAction);
}

} // extern C
