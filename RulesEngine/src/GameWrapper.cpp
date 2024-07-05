#include "GameWrapper.h"

#include "TurnAction.h"
#include "Game.h"

using namespace Redacted;


void* Game_Create()
{
    std::random_device rd;
    return Game_Create_Seeded(rd());
}

void* Game_Create_Seeded(unsigned int seed)
{
    return new Game(players, seed);
}

void Game_Destroy(void* gamePtr)
{
    delete (Game*)gamePtr;
}

bool AddPlayer(void* gamePtr, const char* playerName)
{
    Game* game = (Game*)gamePtr;
    return game.AddPlayer(playerName);
}

bool StartGame(void* gamePtr)
{
    Game* game = (Game*)gamePtr;
    return game.StartGame();
}

bool PlayCard(void* gamePtr, Player& sourcePlayer, Card& sourceCard)
{
    Game* game = (Game*)gamePtr;

    // Perform the Action.
    return game->PlayCard(sourcePlayer, sourceCard);

    // // Return a TurnAction that represents what happened.
    // // It's also sent over the network when needed.
    // TurnAction turnAction;

    // // Just have that thing contain pointers.
    // // toBytes can convert from pointers to etc.
    
    // // Get player index.
    // auto it = std::find_if(game->players.begin(), game->players.end(), [&sourcePlayer](const Player& player)
    //                        { return &sourcePlayer == &player; });
    // int playerIndex = std::distance(game->players.begin(), it);
    // turnAction.sourcePlayerIndex = playerIndex;




    // // Find player by name.
    // auto it = std::find_if(game->players.begin(), game->players.end(), [&playerName](const Player& player)
    //                        { return player.name == playerName; });
    // int playerIndex = std::distance(game->players.begin(), it);

    // Player& sourcePlayer = game->players.at(playerIndex);

    // if (cardIndex >= sourcePlayer.hand.size())
    // {
    //     return false;
    // }

    // Card& sourceCard = sourcePlayer.hand.at(cardIndex);
    // TurnAction turnAction;
    // turnAction.type = TurnAction::Type::PlayCard;
    // turnAction.sourcePlayer = &sourcePlayer;
    // turnAction.sourceCard = &sourceCard;
    // return game->Perform(turnAction);
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

bool MoveToLocation(void* gamePtr, const char* playerName, int cardIndex, int locationIndex)
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

    Card& sourceCard = sourcePlayer.field.at(locationIndex);

    if (locationIndex >= sourcePlayer.field.size())
    {
        return false;
    }

    Card& targetCard = sourcePlayer.field.at(cardIndex);

    TurnAction turnAction;
    turnAction.type = TurnAction::Type::MoveToLocation;
    turnAction.sourcePlayer = &sourcePlayer;
    turnAction.sourceCard = &sourceCard;
    turnAction.targetCard = &targetCard;
    return game->Perform(turnAction);
}

bool CanPlay(void* gamePtr, const char* playerName, int cardIndex)
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

    return sourcePlayer.CanPlay(sourceCard);
}

bool CanInk(void* gamePtr, const char* playerName, int cardIndex)
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

    return sourcePlayer.CanInk(sourceCard);
}

bool CanChallenge(void* gamePtr, const char* playerName, int cardIndex)
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

    return game->CanChallenge(sourcePlayer, sourceCard);
}

bool CanChallengeTarget(void* gamePtr, const char* playerName1, int cardIndex1, const char* playerName2, int cardIndex2)
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

    return game->CanChallengeTarget(sourcePlayer, sourceCard, targetPlayer, targetCard);
}

bool CanChoose(void* gamePtr, const char* playerName1, int cardIndex1, const char* playerName2, int cardIndex2)
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

    return game->CanChoose(sourcePlayer, sourceCard, targetPlayer, targetCard);
}

bool CanQuest(void* gamePtr, const char* playerName, int cardIndex)
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

    return game->CanQuest(sourcePlayer, sourceCard);
}

bool CanMove(void* gamePtr, const char* playerName, int cardIndex, int locationIndex)
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

    if (locationIndex >= sourcePlayer.field.size())
    {
        return false;
    }

    Card& targetCard = sourcePlayer.field.at(locationIndex);

    return sourcePlayer.CanMove(sourceCard, targetCard);
}
