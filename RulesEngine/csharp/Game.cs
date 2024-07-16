using System.Collections.Generic;

namespace LORE {

/*
 * This code is complicated and hard to read.
 *
 * TODO: looking for a simpler way to do this.
 */
public class Game {

	private SWIGTYPE_p_void lore_game = null;

    private static Game thisGame = null;
    static Game ThisGame
    {
        get {
            if (thisGame == null)
            {
                thisGame = new Game();
                thisGame.lore_game = wrapper.Game_Create();
            }
            return thisGame;
        }
    }

    private Dictionary<object, LORE_Card> cards;
    private Dictionary<object, LORE_Player> players;

    Dictionary<object, LORE_Card> Cards
    {
        get {
            return ThisGame.cards
        }
    }

    Dictionary<object, LORE_Player> Players
    {
        get {
            return ThisGame.players
        }
    }

    // TODO: maybe be able to pass playerInterface here.
    public static bool AddPlayer(object player, string playerName)
    {
        LORE_Player lore_player = wrapper.AddPlayer(ThisGame.lore_game, playerName);
        ThisGame.players[player] = lore_player;
        return true;
    }

    public static bool Start()
    {
        return wrapper.StartGame(ThisGame.lore_game);
    }

    public static LORE_TurnAction Mulligan(object player, List<object> cards)
    {
        // Find the player instance.
        LORE_Player lore_player = ThisGame.players[player];
        List<LORE_Card> lore_cards = new List<LORE_Card>();
        foreach (object card in cards)
        {
            lore_cards.Add(ThisGame.cards[card]);
        }

        return wrapper.Mulligan(lore_player, lore_cards);
    }

    public static LORE_TurnAction PlayCard(object player, object card)
    {
        LORE_Player lore_player = ThisGame.players[player];
        LORE_Card lore_card = ThisGame.cards[card];
        return wrapper.PlayCard(ThisGame.lore_game, lore_player, lore_card);
    }

}

} // Namespace LORE
