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
        ThisGame.lore_game = game.Game_Create();
        return true;
    }

    public static bool AddPlayer(object player, string playerName)
    {
        LORE_Player lore_player = game.AddPlayer(ThisGame.lore_game, playerName);
        ThisGame.players[player] = lore_player;
        return true;
    }

    public static bool Start()
    {
        return game.Start(ThisGame.lore_game);
    }

    public static bool Mulligan(object player, List<object> cards)
    {
        // Find the player instance.
        LORE_Player lore_player = ThisGame.players[player];
        List<LORE_Card> lore_cards = new List<LORE_Card>();
        foreach (object card in cards)
        {
            lore_cards.Add(ThisGame.cards[card]);
        }

        game.Mulligan(lore_player, lore_cards);
    }

    public static LORE_Card Card(object csharpObject)
    {
        return ThisGame.cards[csharpObject];
    }

}

} // Namespace LORE
