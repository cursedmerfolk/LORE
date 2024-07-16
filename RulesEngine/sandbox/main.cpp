#include <cassert>
#include <iostream>

#include "GameWrapper.h"
#include "Game.h"

int main() {

    Redacted::Game* game = (Redacted::Game*)Game_Create_Seeded(1234);
    AddPlayer(game, "playerName1");
    AddPlayer(game, "playerName2");
    Redacted::Player& player1 = game->players.at(0);
    Redacted::Player& player2 = game->players.at(1);

    assert(player1.hand.size() == 7);
    assert(player2.hand.size() == 7);

    assert(!PlayCard(game, player1, player1.hand[0]).succeeded);
    assert(!PlayCard(game, player1, player2.hand[0]).succeeded);
    
    std::vector<std::string> expected = {
        "Stitch - Rock Star",
        "Cleansing Rainwater",
        "Arthur - Trained Swordsman",
        "LeFou - Bumbler",
        "Lost in the Woods",
        "The Queen - Wicked and Vain",
        "Sumerian Talisman",
    };

    for (size_t i = 0; i < expected.size(); ++i)
    {
        assert(expected[i] == player1.hand[i].fullName);
    }

    int player1Mull[]{0, 1, 2};
    int player2Mull[]{3, 4, 5, 6};

    assert(Mulligan(game, "playerName1", player1Mull, sizeof(player1Mull) / sizeof(int)).succeeded);
    assert(Mulligan(game, "playerName2", player2Mull, sizeof(player2Mull) / sizeof(int)).succeeded);

    assert(player2.hand.size() == 7);
    
    expected = {
        "LeFou - Bumbler",
        "Lost in the Woods",
        "The Queen - Wicked and Vain",
        "Sumerian Talisman",
        "It Calls Me",
        "Jim Hawkins - Space Traveler",
        "Bruno Madrigal - Undetected Uncle",
    };

    for (size_t i = 0; i < expected.size(); ++i)
    {
        assert(expected[i] == player1.hand[i].fullName);
    }

    assert(game->currentPhase == Redacted::Game::Phase::Main);
    assert(game->currentPlayer == &player1);

    assert(!Mulligan(game, "playerName1", player1Mull, sizeof(player1Mull) / sizeof(int)));
    assert(!Mulligan(game, "playerName2", player2Mull, sizeof(player2Mull) / sizeof(int)));


    // Player 1 turn
    assert(InkCard(game, "playerName1", 6));      // Bruno Madrigal - Undetected Uncle
    assert(player1.hand.size() == 6);
    assert(!PlayCard(game, "playerName1", 0));    // LeFou - Bumbler
    assert(PlayCard(game, "playerName1", 4));     // It Calls Me
    assert(player1.discard.at(0).fullName == "It Calls Me");
    assert(!InkCard(game, "playerName1", 0));     // Already inked.
    assert(!QuestCard(game, "playerName1", 0));   // Nothing at position 0.


    assert(player2.hand.size() == 7);
    assert(!PassTurn(game, "playerName2"));
    assert(PassTurn(game, "playerName1"));
    assert(game->currentPlayer == &player2);
    assert(player2.hand.size() == 8);


    // Player 2 turn
    assert(!InkCard(game, "playerName1", 0));
    assert(InkCard(game, "playerName2", 0));

    expected = {
        "Gramma Tala - Spirit of the Ocean",
        "Let It Go",
        "Elsa - Gloves Off",
        "Rufus - Orphanage Cat",
        "The Firebird - Force of Destruction",
        "HeiHei - Accidental Explorer",
        "Pongo - Determined Father",
    };

    for (size_t i = 0; i < expected.size(); ++i)
    {
        assert(expected[i] == player2.hand[i].fullName);
    }

    assert(!PlayCard(game, "playerName1", 0));    // Wrong turn
    assert(!PlayCard(game, "playerName2", 0));    // Gramma Tala - Spirit of the Ocean
    assert(!PassTurn(game, "playerName1"));
    assert(!InkCard(game, "playerName2", 6));
    assert(PassTurn(game, "playerName2"));
    assert(game->currentPlayer == &player1);
    assert(player1.hand.size() == 6);

    // Player 1 turn
    assert(!PlayCard(game, "playerName1", 0));    // LeFou - Bumbler
    assert(InkCard(game, "playerName1", 1));
    assert(PlayCard(game, "playerName1", 0));     // LeFou - Bumbler
    assert(!QuestCard(game, "playerName1", 0));   // LeFou - Bumbler is not Dry.
    assert(player1.hand.size() == 4);
    assert(!ChallengeCard(game, "playerName1", 0, "playerName2", 0));  // Nothing on player 2 field.
    assert(!ChallengeCard(game, "playerName2", 0, "playerName1", 0));  // Nothing on player 2 field.
    assert(PassTurn(game, "playerName1"));
    assert(game->currentPlayer == &player2);

    // Player 2 turn
    assert(InkCard(game, "playerName2", 1));      // Let It Go
    assert(PlayCard(game, "playerName2", 4));     // HeiHei - Accidental Explorer
    assert(!ChallengeCard(game, "playerName1", 0, "playerName1", 0));
    assert(!ChallengeCard(game, "playerName2", 0, "playerName2", 0));
    assert(!ChallengeCard(game, "playerName2", 0, "playerName1", 0));  // HeiHei is not dry yet.
    assert(PassTurn(game, "playerName2"));

    // Player 1 turn
    assert(InkCard(game, "playerName1", 0));  // The Queen - Wicked and Vain
    assert(!ChallengeCard(game, "playerName2", 0, "playerName1", 0));  // Wrong source player
    assert(ChallengeCard(game, "playerName1", 0, "playerName2", 0));
    assert(player2.field.at(0).damageCounters == 1);  // HeiHei - Accidental Explorer (3/2)
    assert(player2.field.size() == 1);    // Lefou in discard
    assert(player1.field.size() == 0);    // Lefou in discard
    assert(player1.discard.size() == 2);  // Lefou and How Far I'll Go in discard

    // Add a location to player1 hand for testing.
    Redacted::Card motunui = filterBy(game->cards, &Redacted::Card::fullName, std::string("Motunui - Island Paradise")).at(0);
    player1.hand.push_back(motunui);
    assert(PlayCard(game, "playerName1", 4));  // Motunui - Island Paradise
    assert(PassTurn(game, "playerName1"));

    // Player 2 turn
    assert(ChallengeCard(game, "playerName2", 0, "playerName1", 0));
    assert(player1.field.size() == 1);
    assert(player2.field.size() == 1);
    assert(player2.field.at(0).isReady == false);  // HeiHei - Accidental Explorer (3/2)
    assert(!ChallengeCard(game, "playerName2", 0, "playerName1", 0));  // HeiHei is exerted.
    assert(!QuestCard(game, "playerName2", 0));                        // HeiHei is exerted.
    assert(PassTurn(game, "playerName2"));

    // Player 1 turn
    assert(player1.loreTotal == 1);  // Gained from Motunui
    assert(PassTurn(game, "playerName1"));

    // Player 2 turn
    assert(ChallengeCard(game, "playerName2", 0, "playerName1", 0));
    assert(player1.field.size() == 0);   // Motunui discarded.
    assert(player1.discard.size() == 3); // Motunui discarded.
    assert(player1.discard.at(2).fullName == "Motunui - Island Paradise"); // Motunui discarded.
    assert(player2.field.size() == 1);  // HeiHei - Accidental Explorer (3/2)


    // TODO: Evasive and Rush.
    // Probably just make standalone tests.

    // for (auto& card : player1.hand)
    // {
    //     std::cout << card.fullName << std::endl;
    // }

    // 

}