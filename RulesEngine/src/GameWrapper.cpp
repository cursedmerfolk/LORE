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
    return new Game(seed);
}

void Game_Destroy(void* gamePtr)
{
    delete (Game*)gamePtr;
}

TurnAction AddPlayer(void* gamePtr, const char* playerName)
{
    Game* game = (Game*)gamePtr;
    
    TurnAction turnAction(TurnAction::Type::AddPlayer);
    turnAction.succeeded = game->AddPlayer(playerName);

    return turnAction;
}

TurnAction StartGame(void* gamePtr)
{
    Game* game = (Game*)gamePtr;
    
    TurnAction turnAction(TurnAction::Type::StartGame);
    turnAction.succeeded = game->StartGame();

    return turnAction;
}

TurnAction PlayCard(void* gamePtr, Player& sourcePlayer, Card& sourceCard, int8_t targetIndex)
{
    Game* game = (Game*)gamePtr;

    // Return a TurnAction that represents what animations need to be perfomed by the UI.
    // It's also sent over the network in the case of multiplayer.
    TurnAction turnAction(TurnAction::Type::PlayCard);
    turnAction.sourcePlayer = &sourcePlayer;
    turnAction.sourceCard = &sourceCard;
    turnAction.targetIndex = targetIndex;

    turnAction.succeeded = game->Perform(turnAction);
    return turnAction;
}

TurnAction ChallengeCard(void* gamePtr, Player& sourcePlayer, Card& sourceCard, Player& targetPlayer, Card& targetCard)
{
    Game* game = (Game*)gamePtr;
    
    TurnAction turnAction(TurnAction::Type::ChallengeCard);
    turnAction.sourcePlayer = &sourcePlayer;
    turnAction.sourceCard = &sourceCard;
    turnAction.targetPlayer = &targetPlayer;
    turnAction.targetCard = &targetCard;

    turnAction.succeeded = game->Perform(turnAction);
    return turnAction;
}

TurnAction InkCard(void* gamePtr, Redacted::Player& sourcePlayer, Redacted::Card& sourceCard)
{
    Game* game = (Game*)gamePtr;

    TurnAction turnAction(TurnAction::Type::InkCard);
    turnAction.sourcePlayer = &sourcePlayer;
    turnAction.sourceCard = &sourceCard;

    turnAction.succeeded = game->Perform(turnAction);
    return turnAction;
}

TurnAction QuestCard(void* gamePtr, Redacted::Player& sourcePlayer, Redacted::Card& sourceCard)
{
    Game* game = (Game*)gamePtr;

    TurnAction turnAction(TurnAction::Type::QuestCard);
    turnAction.sourcePlayer = &sourcePlayer;
    turnAction.sourceCard = &sourceCard;

    turnAction.succeeded = game->Perform(turnAction);
    return turnAction;
}

TurnAction Mulligan(void* gamePtr, Redacted::Player& sourcePlayer, std::vector<Redacted::Card> mulligans)
{
    Game* game = (Game*)gamePtr;

    TurnAction turnAction(TurnAction::Type::Mulligan);
    turnAction.sourcePlayer = &sourcePlayer;
    turnAction.mulligans = &mulligans;

    turnAction.succeeded = game->Perform(turnAction);
    return turnAction;
}

TurnAction PassTurn(void* gamePtr, Redacted::Player& sourcePlayer)
{
    Game* game = (Game*)gamePtr;

    TurnAction turnAction(TurnAction::Type::PassTurn);
    turnAction.sourcePlayer = &sourcePlayer;

    turnAction.succeeded = game->Perform(turnAction);
    return turnAction;
}

TurnAction MoveToLocation(void* gamePtr, Redacted::Player& sourcePlayer, Redacted::Card& sourceCard, Redacted::Card& targetLocation)
{
    Game* game = (Game*)gamePtr;

    TurnAction turnAction(TurnAction::Type::MoveToLocation);
    turnAction.sourcePlayer = &sourcePlayer;
    turnAction.sourceCard = &sourceCard;
    turnAction.targetCard = &targetLocation;

    turnAction.succeeded = game->Perform(turnAction);
    return turnAction;
}

// TurnAction CanPlay(void* gamePtr, Redacted::Player& sourcePlayer, Redacted::Card& sourceCard)
// {
//     Game* game = (Game*)gamePtr;

//     // Find player by name.
//     auto it = std::find_if(game->players.begin(), game->players.end(), [&playerName](const Player& player)
//                            { return player.name == playerName; });
//     int playerIndex = std::distance(game->players.begin(), it);

//     Player& sourcePlayer = game->players.at(playerIndex);

//     if (cardIndex >= sourcePlayer.hand.size())
//     {
//         return false;
//     }

//     Card& sourceCard = sourcePlayer.hand.at(cardIndex);

//     return sourcePlayer.CanPlay(sourceCard);
// }

// TurnAction CanInk(void* gamePtr, Redacted::Player& sourcePlayer, Redacted::Card& sourceCard)
// {
//     Game* game = (Game*)gamePtr;

//     // Find player by name.
//     auto it = std::find_if(game->players.begin(), game->players.end(), [&playerName](const Player& player)
//                            { return player.name == playerName; });
//     int playerIndex = std::distance(game->players.begin(), it);

//     Player& sourcePlayer = game->players.at(playerIndex);

//     if (cardIndex >= sourcePlayer.hand.size())
//     {
//         return false;
//     }

//     Card& sourceCard = sourcePlayer.hand.at(cardIndex);

//     return sourcePlayer.CanInk(sourceCard);
// }

// TurnAction CanChallenge(void* gamePtr, Redacted::Player& sourcePlayer, Redacted::Card& sourceCard)
// {
//     Game* game = (Game*)gamePtr;

//     // Find player by name.
//     auto it = std::find_if(game->players.begin(), game->players.end(), [&playerName](const Player& player)
//                            { return player.name == playerName; });
//     int playerIndex = std::distance(game->players.begin(), it);

//     Player& sourcePlayer = game->players.at(playerIndex);

//     if (cardIndex >= sourcePlayer.field.size())
//     {
//         return false;
//     }

//     Card& sourceCard = sourcePlayer.field.at(cardIndex);

//     return game->CanChallenge(sourcePlayer, sourceCard);
// }

// TurnAction CanChallengeTarget(void* gamePtr, const char* playerName1, int cardIndex1, const char* playerName2, int cardIndex2)
// {
//     Game* game = (Game*)gamePtr;

//     // Find player by name.
//     auto it = std::find_if(game->players.begin(), game->players.end(), [&playerName1](const Player& player)
//                            { return player.name == playerName1; });
//     int playerIndex = std::distance(game->players.begin(), it);

//     Player& sourcePlayer = game->players.at(playerIndex);

//     if (cardIndex1 >= sourcePlayer.field.size())
//     {
//         return false;
//     }

//     Card& sourceCard = sourcePlayer.field.at(cardIndex1);

//     it = std::find_if(game->players.begin(), game->players.end(), [&playerName2](const Player& player)
//                       { return player.name == playerName2; });
//     playerIndex = std::distance(game->players.begin(), it);

//     Player& targetPlayer = game->players.at(playerIndex);

//     if (cardIndex2 >= targetPlayer.field.size())
//     {
//         return false;
//     }

//     Card& targetCard = targetPlayer.field.at(cardIndex2);

//     return game->CanChallengeTarget(sourcePlayer, sourceCard, targetPlayer, targetCard);
// }

// TurnAction CanChoose(void* gamePtr, const char* playerName1, int cardIndex1, const char* playerName2, int cardIndex2)
// {
//     Game* game = (Game*)gamePtr;

//     // Find player by name.
//     auto it = std::find_if(game->players.begin(), game->players.end(), [&playerName1](const Player& player)
//                            { return player.name == playerName1; });
//     int playerIndex = std::distance(game->players.begin(), it);

//     Player& sourcePlayer = game->players.at(playerIndex);

//     if (cardIndex1 >= sourcePlayer.field.size())
//     {
//         return false;
//     }

//     Card& sourceCard = sourcePlayer.field.at(cardIndex1);

//     it = std::find_if(game->players.begin(), game->players.end(), [&playerName2](const Player& player)
//                       { return player.name == playerName2; });
//     playerIndex = std::distance(game->players.begin(), it);

//     Player& targetPlayer = game->players.at(playerIndex);

//     if (cardIndex2 >= targetPlayer.field.size())
//     {
//         return false;
//     }

//     Card& targetCard = targetPlayer.field.at(cardIndex2);

//     return game->CanChoose(sourcePlayer, sourceCard, targetPlayer, targetCard);
// }

// TurnAction CanQuest(void* gamePtr, Redacted::Player& sourcePlayer, Redacted::Card& sourceCard)
// {
//     Game* game = (Game*)gamePtr;

//     // Find player by name.
//     auto it = std::find_if(game->players.begin(), game->players.end(), [&playerName](const Player& player)
//                            { return player.name == playerName; });
//     int playerIndex = std::distance(game->players.begin(), it);

//     Player& sourcePlayer = game->players.at(playerIndex);

//     if (cardIndex >= sourcePlayer.field.size())
//     {
//         return false;
//     }

//     Card& sourceCard = sourcePlayer.field.at(cardIndex);

//     return game->CanQuest(sourcePlayer, sourceCard);
// }

// TurnAction CanMove(void* gamePtr, Redacted::Player& sourcePlayer, Redacted::Card& sourceCard, int locationIndex)
// {
//     Game* game = (Game*)gamePtr;

//     // Find player by name.
//     auto it = std::find_if(game->players.begin(), game->players.end(), [&playerName](const Player& player)
//                            { return player.name == playerName; });
//     int playerIndex = std::distance(game->players.begin(), it);

//     Player& sourcePlayer = game->players.at(playerIndex);

//     if (cardIndex >= sourcePlayer.field.size())
//     {
//         return false;
//     }

//     Card& sourceCard = sourcePlayer.field.at(cardIndex);

//     if (locationIndex >= sourcePlayer.field.size())
//     {
//         return false;
//     }

//     Card& targetCard = sourcePlayer.field.at(locationIndex);

//     return sourcePlayer.CanMove(sourceCard, targetCard);
// }
