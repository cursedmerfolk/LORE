#include <cassert>
#include <iostream>

#include "GameWrapper.h"
#include "Game.h"

int main() {

    Lorcana::Game* game = (Lorcana::Game*)Game_Create_Seed("playerName1", "playerName2", 1234);
    Lorcana::Player& player1 = game->players.at(0);
    Lorcana::Player& player2 = game->players.at(1);

    assert(player1.hand.size() == 7);
    assert(player2.hand.size() == 7);

    assert(!PlayCard(game, "playerName1", 0));
    assert(!PlayCard(game, "playerName2", 0));
    
    std::vector<std::string> player1_expected = {
        "Stitch - Rock Star",
        "Cleansing Rainwater",
        "Arthur - Trained Swordsman",
        "LeFou - Bumbler",
        "Lost in the Woods",
        "The Queen - Wicked and Vain",
        "Sumerian Talisman",
    };

    for (size_t i = 0; i < player1_expected.size(); ++i)
    {
        assert(player1_expected[i] == player1.hand[i].fullName);
    }

    int player1Mull[]{0, 1, 2};
    int player2Mull[]{3, 4, 5, 6};

    assert(Mulligan(game, "playerName1", player1Mull, sizeof(player1Mull) / sizeof(int)));
    assert(Mulligan(game, "playerName2", player2Mull, sizeof(player2Mull) / sizeof(int)));

    // assert(player1.hand.size() == 7);
    assert(player2.hand.size() == 7);
    
    player1_expected = {
        "LeFou - Bumbler",
        "Lost in the Woods",
        "The Queen - Wicked and Vain",
        "Sumerian Talisman",
        "It Calls Me",
        "Jim Hawkins - Space Traveler",
        "Bruno Madrigal - Undetected Uncle",
    };

    for (size_t i = 0; i < player1_expected.size(); ++i)
    {
        assert(player1_expected[i] == player1.hand[i].fullName);
    }

    assert(game->currentPhase == Lorcana::Phase::Main);
    assert(game->currentPlayer == &player1);

    assert(!Mulligan(game, "playerName1", player1Mull, sizeof(player1Mull) / sizeof(int)));
    assert(!Mulligan(game, "playerName2", player2Mull, sizeof(player2Mull) / sizeof(int)));


    // Player 1 turn
    assert(InkCard(game, "playerName1", 0));
    assert(player1.hand.size() == 6);
    assert(!PlayCard(game, "playerName1", 0));  // Cost 4
    assert(PlayCard(game, "playerName1", 3));  // Cost 1
    assert(!InkCard(game, "playerName1", 0));  // Already inked.
    assert(!QuestCard(game, "playerName1", 0));  // Not dry.

}