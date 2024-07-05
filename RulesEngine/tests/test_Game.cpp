#include <gtest/gtest.h>

#include "GameWrapper.h"
#include "Util.h"
#include "Card.h"
#include "Player.h"
#include "Game.h"

// Demonstrate some basic assertions.
TEST(Test_GameWrapper, Basic)
{

    Redacted::Game* game = (Redacted::Game*)Game_Create("playerName1", "playerName2");

    EXPECT_FALSE(PlayCard(game, "playerName1", 0));
    EXPECT_FALSE(PlayCard(game, "playerName2", 0));

    int player1Mull[]{1, 2, 3};
    int player2Mull[]{4, 5, 6, 7};

    EXPECT_TRUE(Mulligan(game, "playerName1", player1Mull, sizeof(player1Mull)));
    EXPECT_TRUE(Mulligan(game, "playerName2", player1Mull, sizeof(player2Mull)));

}
