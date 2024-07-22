using System.Collections.Generic;

namespace LORE
{

    /*
     * This code is complicated and hard to read.
     *
     * TODO: looking for a simpler way to do this.
     */
    public class Game
    {

        private SWIGTYPE_p_void lore_game = null;

        private static Game thisGame = null;
        static Game ThisGame
        {
            get
            {
                if (thisGame == null)
                {
                    thisGame = new Game();
                    thisGame.lore_game = wrapper.Game_Create();
                }
                return thisGame;
            }
        }

        private Dictionary<object, LORE_Card> cards = new Dictionary<object, LORE_Card>();
        private Dictionary<object, LORE_Player> players = new Dictionary<object, LORE_Player>();

        public static Dictionary<object, LORE_Card> Cards
        {
            get
            {
                return ThisGame.cards;
            }
        }

        public static Dictionary<object, LORE_Player> Players
        {
            get
            {
                return ThisGame.players;
            }
        }

        public static bool AddPlayer(PlayerInterface player)
        {
            LORE_TurnAction turnAction = wrapper.AddPlayer(ThisGame.lore_game, player.Name);
            if (turnAction.sourcePlayer == null)
            {
                return false;
            }
            Players[player] = turnAction.sourcePlayer;
            return true;
        }

        public static bool Start()
        {
            return wrapper.StartGame(ThisGame.lore_game).succeeded;
        }

        public static LORE_TurnAction Mulligan(object player, List<byte> cards)
        {
            LORE_Player lore_player = Players[player];
            return wrapper.Mulligan(lore_player, cards);
        }

        public static LORE_TurnAction PlayCard(object player, object card)
        {
            LORE_Player lore_player = Players[player];
            LORE_Card lore_card = Cards[card];
            return wrapper.PlayCard(ThisGame.lore_game, lore_player, lore_card);
        }

        public static LORE_TurnAction PassTurn(object player)
        {
            LORE_Player lore_player = Players[player];
            return wrapper.PassTurn(ThisGame.lore_game, lore_player);
        }

    }

} // Namespace LORE
