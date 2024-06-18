using System;
using System.Collections.Generic;

namespace Lorcana
{

	public partial class Game
	{
		// These will probably need reference to the Game at some point.
		public static bool Elsa_SnowQueen_Freeze(TurnAction turnAction)
		{
			Card sourceCard = turnAction.sourceCard;
			Card targetCard = turnAction.targetCard;

			if (!sourceCard.isReady)
			{
				return false;
			}

			// Exert this card.
			sourceCard.isReady = false;

			// Exert the chosen card.
			targetCard.isReady = false;

			return true;
		}

		public static Dictionary<string, Func<TurnAction, bool>> Abilities = new Dictionary<string, Func<TurnAction, bool>>
		{
			{ "elsa_snowqueen_freeze", Elsa_SnowQueen_Freeze },
		};

	}

}
