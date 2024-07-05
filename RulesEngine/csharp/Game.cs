using System.Collections.Generic;

namespace LORE {

/*
 * TODO: looking for a simpler way to do this.
 */
public class Game {

    private static Game thisGame = null;
    static Game ThisGame
    {
        get {
            if (thisGame == null)
            {
                thisGame = new Game();
            }
            return thisGame;
        }
    }
	private SWIGTYPE_p_void lore_game;

    private Dictionary<object, LORE_Player> players;
    private Dictionary<object, LORE_Card> cards;

    public static (LORE_Player, LORE_Player) Start(string playerName1, string playerName2)
    {
        ThisGame.lore_game = game.Game_Create("test1", "test2");
        return true;
    }

    public static bool Start(object Player, string playerName2)
    {
        game.Mulligan(ThisGame.lore_game, );
        return true;
    }

    public static LORE_Card Card(object csharpObject)
    {
        return ThisGame.cards[csharpObject];
    }

}

} // Namespace LORE
