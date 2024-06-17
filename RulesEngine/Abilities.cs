using System;
using System.Collections.Generic;

//[JsType(JsMode.Global, Filename="Game.js")]
namespace Lorcana
{

	public partial class Game
	{
        // These will probably need reference to the Game at some point.
        public static bool Elsa_SnowQueen_Freeze(TurnAction turnAction)
        {
            Card sourceCard = turnAction.SourceCard;
            Card targetCard = turnAction.TargetCard;

            if (!sourceCard.IsReady)
            {
                return false;
            }

            // Exert this card.
            sourceCard.IsReady = false;

            // Exert the chosen card.
            targetCard.IsReady = false;

            return true;
        }

        public static Dictionary<string, Func<TurnAction, bool>> Abilities = new Dictionary<string, Func<TurnAction, bool>>
        {
            { "elsa_snowqueen_freeze", Elsa_SnowQueen_Freeze },
        };

    }

}