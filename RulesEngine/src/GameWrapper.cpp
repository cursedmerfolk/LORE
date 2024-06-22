#include "GameWrapper.h"

#include "Game.h"

using namespace Lorcana;


void* Game_Create(const char* player1, const char* player2)
{
    std::random_device rd;
    return Game_Create_Seeded(player1, player2, rd());
}

void* Game_Create_Seeded(const char* player1, const char* player2, unsigned int seed)
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

    Player& sourcePlayer = game->players.at(playerIndex);

    if (cardIndex >= sourcePlayer.hand.size())
    {
        return false;
    }

    Card& sourceCard = sourcePlayer.hand.at(cardIndex);
    TurnAction turnAction;
    turnAction.type = TurnAction::Type::PlayCard;
    turnAction.sourcePlayer = &sourcePlayer;
    turnAction.sourceCard = &sourceCard;
    return game->Perform(turnAction);
}

bool ChallengeCard(void* gamePtr, const char* playerName1, int cardIndex1, const char* playerName2, int cardIndex2)
{
    Game* game = (Game*)gamePtr;

    // Find player by name.
    auto it = std::find_if(game->players.begin(), game->players.end(), [&playerName1](const Player& player)
                           { return player.name == playerName1; });
    int playerIndex = std::distance(game->players.begin(), it);

    Player& sourcePlayer = game->players.at(playerIndex);

    if (cardIndex1 >= sourcePlayer.field.size())
    {
        return false;
    }

    Card& sourceCard = sourcePlayer.field.at(cardIndex1);

    it = std::find_if(game->players.begin(), game->players.end(), [&playerName2](const Player& player)
                      { return player.name == playerName2; });
    playerIndex = std::distance(game->players.begin(), it);

    Player& targetPlayer = game->players.at(playerIndex);

    if (cardIndex2 >= targetPlayer.field.size())
    {
        return false;
    }

    Card& targetCard = targetPlayer.field.at(cardIndex2);
    
    TurnAction turnAction;
    turnAction.type = TurnAction::Type::ChallengeCard;
    turnAction.sourcePlayer = &sourcePlayer;
    turnAction.sourceCard = &sourceCard;
    turnAction.targetPlayer = &targetPlayer;
    turnAction.targetCard = &targetCard;

    return game->Perform(turnAction);
}

bool InkCard(void* gamePtr, const char* playerName, int cardIndex)
{
    Game* game = (Game*)gamePtr;

    // Find player by name.
    auto it = std::find_if(game->players.begin(), game->players.end(), [&playerName](const Player& player)
                           { return player.name == playerName; });
    int playerIndex = std::distance(game->players.begin(), it);

    Player& sourcePlayer = game->players.at(playerIndex);

    if (cardIndex >= sourcePlayer.hand.size())
    {
        return false;
    }

    Card& sourceCard = sourcePlayer.hand.at(cardIndex);
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

    Player& sourcePlayer = game->players.at(playerIndex);

    if (cardIndex >= sourcePlayer.field.size())
    {
        return false;
    }

    Card& sourceCard = sourcePlayer.field.at(cardIndex);
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

    Player& sourcePlayer = game->players.at(playerIndex);

    // Add all ints to turnAction.mulligans
    std::vector<uint8_t> mulligans(cardIndices, cardIndices + arrayLength); 

    TurnAction turnAction;
    turnAction.type = TurnAction::Type::Mulligan;
    turnAction.sourcePlayer = &sourcePlayer;
    turnAction.mulligans = &mulligans;

    return game->Perform(turnAction);
}

bool PassTurn(void* gamePtr, const char* playerName)
{
    Game* game = (Game*)gamePtr;

    // Find player by name.
    auto it = std::find_if(game->players.begin(), game->players.end(), [&playerName](const Player& player)
                           { return player.name == playerName; });
    int playerIndex = std::distance(game->players.begin(), it);

    Player& sourcePlayer = game->players.at(playerIndex);

    TurnAction turnAction;
    turnAction.type = TurnAction::Type::PassTurn;
    turnAction.sourcePlayer = &sourcePlayer;

    return game->Perform(turnAction);
}
