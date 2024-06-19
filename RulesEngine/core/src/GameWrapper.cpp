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

    // Find player by name.
    auto it = std::find_if(game->players.begin(), game->players.end(), [&playerName](const Player& player) {
        return player.name == playerName;
    });
    int playerIndex = std::distance(game->players.begin(), it);

    Player sourcePlayer = game->players[playerIndex];
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

    // Find player by name.
    auto it = std::find_if(game->players.begin(), game->players.end(), [&playerName](const Player& player) {
        return player.name == playerName;
    });
    int playerIndex = std::distance(game->players.begin(), it);

    Player sourcePlayer = game->players[playerIndex];
    Card sourceCard = sourcePlayer.hand[cardIndex];
    TurnAction turnAction;
    turnAction.type = TurnAction::Type::InkCard;
    turnAction.sourcePlayer = sourcePlayer;
    turnAction.sourceCard = sourceCard;
    game->Perform(turnAction);
}
