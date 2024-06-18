#include "GameWrapper.h"
#include "Game.h"

using namespace Lorcana;

void* Game_Create(const char* player1, const char* player2) {
    std::vector<std::string> players{player1, player2};
    return new Game(players);
}

void Game_Destroy(void* gamePtr) {
    delete (Game*)gamePtr;
}

void PlayCard(void* gamePtr, const char* playerName, int cardIndex)
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

void InkCard(void* gamePtr, const char* playerName, int cardIndex)
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
