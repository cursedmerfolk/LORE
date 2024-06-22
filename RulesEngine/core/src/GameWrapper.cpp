#include "GameWrapper.h"

#include "Game.h"

using namespace Lorcana;


void* Game_Create(const char* player1, const char* player2)
{
    std::random_device rd;
    return Game_Create_Seed(player1, player2, rd());
}

void* Game_Create_Seed(const char* player1, const char* player2, unsigned int seed)
{
    std::vector<std::string> players{player1, player2};
    return new Game(players, seed);
}

void Game_Destroy(void* gamePtr)
{
    delete (Game*)gamePtr;
}

bool PlayCard(void* gamePtr, const char* playerName, int cardIndex)
{
    Game* game = (Game*)gamePtr;

    // Find player by name.
    auto it = std::find_if(game->players.begin(), game->players.end(), [&playerName](const Player& player)
                           { return player.name == playerName; });
    int playerIndex = std::distance(game->players.begin(), it);

    Player& sourcePlayer = game->players[playerIndex];
    Card& sourceCard = sourcePlayer.hand[cardIndex];
    TurnAction turnAction;
    turnAction.type = TurnAction::Type::PlayCard;
    turnAction.sourcePlayer = &sourcePlayer;
    turnAction.sourceCard = &sourceCard;
    return game->Perform(turnAction);
}

bool InkCard(void* gamePtr, const char* playerName, int cardIndex)
{
    Game* game = (Game*)gamePtr;

    // Find player by name.
    auto it = std::find_if(game->players.begin(), game->players.end(), [&playerName](const Player& player)
                           { return player.name == playerName; });
    int playerIndex = std::distance(game->players.begin(), it);

    Player& sourcePlayer = game->players[playerIndex];
    Card& sourceCard = sourcePlayer.hand[cardIndex];
    TurnAction turnAction;
    turnAction.type = TurnAction::Type::InkCard;
    turnAction.sourcePlayer = &sourcePlayer;
    turnAction.sourceCard = &sourceCard;
    return game->Perform(turnAction);
}

bool QuestCard(void* gamePtr, const char* playerName, int cardIndex)
{
    Game* game = (Game*)gamePtr;

    // Find player by name.
    auto it = std::find_if(game->players.begin(), game->players.end(), [&playerName](const Player& player)
                           { return player.name == playerName; });
    int playerIndex = std::distance(game->players.begin(), it);

    Player& sourcePlayer = game->players[playerIndex];
    Card& sourceCard = sourcePlayer.field[cardIndex];
    TurnAction turnAction;
    turnAction.type = TurnAction::Type::QuestCard;
    turnAction.sourcePlayer = &sourcePlayer;
    turnAction.sourceCard = &sourceCard;
    return game->Perform(turnAction);
}

bool Mulligan(void* gamePtr, const char* playerName, int* cardIndices, int arrayLength)
{
    Game* game = (Game*)gamePtr;

    // Find player by name.
    auto it = std::find_if(game->players.begin(), game->players.end(), [&playerName](const Player& player)
                           { return player.name == playerName; });
    int playerIndex = std::distance(game->players.begin(), it);

    Player& sourcePlayer = game->players[playerIndex];

    // Add all ints to turnAction.mulligans
    std::vector<uint8_t> mulligans(cardIndices, cardIndices + arrayLength); 

    TurnAction turnAction;
    turnAction.type = TurnAction::Type::Mulligan;
    turnAction.sourcePlayer = &sourcePlayer;
    turnAction.mulligans = &mulligans;

    return game->Perform(turnAction);
}
