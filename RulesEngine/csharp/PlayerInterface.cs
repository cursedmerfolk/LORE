using System.Collections.Generic;


namespace LORE
{

	public interface PlayerInterface
	{

		public byte Id
		{
			get
			{
				return Game.Players[this].id;
			}
			set
			{
				Game.Players[this].id = value;
			}
		}

		public byte LoreTotal
		{
			get
			{
				return Game.Players[this].loreTotal;
			}
			set
			{
				Game.Players[this].loreTotal = value;
			}
		}

		public string Name
		{
			get
			{
				return Game.Players[this].name;
			}
			set
			{
				Game.Players[this].name = value;
			}
		}

		// I'm not sure how to handle these yet.
		// public List<LORE_Card> Hand
		// {
		//     get
		//     {
		//         return Game.Players[this].hand;
		//     }
		//     set
		//     {
		//         Game.Players[this].hand = value;
		//     }
		// }


		// public List<LORE_Card> Field
		// {
		//     get
		//     {
		//         return Game.Players[this].field;
		//     }
		//     set
		//     {
		//         Game.Players[this].field = value;
		//     }
		// }

		// public List<LORE_Card> Discard
		// {
		//     get
		//     {
		//         return Game.Players[this].discard;
		//     }
		//     set
		//     {
		//         Game.Players[this].discard = value;
		//     }
		// }

		// public List<LORE_Card> Deck
		// {
		//     get
		//     {
		//         return Game.Players[this].deck;
		//     }
		//     set
		//     {
		//         Game.Players[this].deck = value;
		//     }
		// }

		// public List<LORE_Card> Inkwell
		// {
		//     get
		//     {
		//         return Game.Players[this].inkwell;
		//     }
		//     set
		//     {
		//         Game.Players[this].inkwell = value;
		//     }
		// }

		public bool DoneMulligan
		{
			get
			{
				return Game.Players[this].doneMulligan;
			}
			set
			{
				Game.Players[this].doneMulligan = value;
			}
		}

		public bool InkedThisTurn
		{
			get
			{
				return Game.Players[this].inkedThisTurn;
			}
			set
			{
				Game.Players[this].inkedThisTurn = value;
			}
		}

	}

} // Namespace LORE
