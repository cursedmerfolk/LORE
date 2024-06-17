using System;
using System.Collections.Generic;

namespace Lorcana
{
	public class Player
	{
		public string Name { get; set; }
		public List<Card> Hand { get; set; }
		public List<Card> Field { get; set; }
		public List<Card> Discard { get; set; }
		public int LoreTotal { get; set; }
		public List<Card> Deck { get; set; }
		public List<Card> Inkwell { get; set; }

		public Player(string name)
		{
			Name = name;
			Hand = new List<Card>();
			Field = new List<Card>();
			Discard = new List<Card>();
			LoreTotal = 0;
			Deck = new List<Card>();
			Inkwell = new List<Card>();
		}

		public bool CanPlay(Card card)
		{
			// Check resource requirements.
			int numReadyInk = 0;
			foreach (Card inkedCard in Inkwell)
			{
				if (inkedCard.IsReady)
				{
					numReadyInk += 1;
				}
			}

			// TODO: enable once Inkwell is implemented.
			// if (card.Cost > numReadyInk)
			// {
			// 	return false;
			// }

			return true;
		}

	}

}
