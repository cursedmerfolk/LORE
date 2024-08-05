using System;
using System.Collections.Generic;
using System.Linq;

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

		private static Game m_instance = null;
		static Game Instance
		{
			get
			{
				if (m_instance == null)
				{
					m_instance = new Game();
					m_instance.lore_game = LORE_Wrapper.Game_Create();
				}
				return m_instance;
			}
		}

		private Dictionary<object, LORE_Card> cards = new Dictionary<object, LORE_Card>();
		private Dictionary<object, LORE_Player> players = new Dictionary<object, LORE_Player>();

		public static Dictionary<object, LORE_Card> Cards
		{
			get
			{
				return Instance.cards;
			}
		}

		public static Dictionary<object, LORE_Player> Players
		{
			get
			{
				return Instance.players;
			}
		}

		public static LORE_Player AddPlayer(object player, string playerName)
		{
            Console.WriteLine("hi1");
			LORE_TurnAction turnAction = LORE_Wrapper.AddPlayer(Instance.lore_game, playerName);
			if (turnAction.sourcePlayer == null)
			{
				return null;
			}
            Console.WriteLine("hi2");

			Players[player] = turnAction.sourcePlayer;
			return turnAction.sourcePlayer;
		}

		public static bool Start()
		{
			return LORE_Wrapper.StartGame(Instance.lore_game).succeeded;
		}

		public static LORE_TurnAction Mulligan(object player, List<object> cards)
		{
			LORE_Player lore_player = Players[player];

			// Convert card objects to indices.
			LORE_ByteVector cardIndices = new LORE_ByteVector();
			foreach(object card in cards)
			{
				LORE_Card lore_card = Cards[card];
				List<LORE_Card> player_hand = lore_card.owner.hand.ToList();
				byte cardIndex = (byte)player_hand.FindIndex(c => c == lore_card);
				cardIndices.Add(cardIndex);

			}

			return LORE_Wrapper.Mulligan(Instance.lore_game, lore_player, cardIndices);
		}

		public static LORE_TurnAction PlayCard(LORE_Card card, sbyte targetIndex)
		{
			LORE_Player lore_player = Players[card.owner];
			LORE_Card lore_card = Cards[card];
			return LORE_Wrapper.PlayCard(Instance.lore_game, lore_player, lore_card, targetIndex);
		}

		public static LORE_Card GetCard(object card)
		{
			return Cards[card];
		}

		public static LORE_TurnAction PassTurn(object player)
		{
			LORE_Player lore_player = Players[player];
			return LORE_Wrapper.PassTurn(Instance.lore_game, lore_player);
		}

	}

} // Namespace LORE
