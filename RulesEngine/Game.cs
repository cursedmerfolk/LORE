using System;
using System.Collections.Generic;

namespace Lorcana
{
	public class TurnAction
	{
		public enum Type
		{
			PlayCard,
			ChallengeCard,
			InkCard,
			QuestCard,
			UseAbility,
		}

		public Type type { get; set; }
		public Player SourcePlayer { get; set; }
		public Card SourceCard { get; set; }
		public Player TargetPlayer { get; set; }
		public Card TargetCard { get; set; }
		public List<Card> Singers { get; set; }
		public string AbilityName { get; set; }
	};

	public partial class Game
	{
		public Dictionary<string, Player> Players { get; set; }

		public Game(List<string> playerNames)
		{
			Players = new Dictionary<string, Player>();

			// Add new Player to Players for each numberPlayers
            foreach (string playerName in playerNames)
            {
                Players[playerName] = new Player(playerName);
            }
		}

		public bool Perform(TurnAction turnAction)
		{
			Console.WriteLine($"Performing Turn Action: {turnAction.type}");

			if (turnAction.type == TurnAction.Type.PlayCard)
			{
				Player sourcePlayer = turnAction.SourcePlayer;
				Card sourceCard = turnAction.SourceCard;

				// Check if there are enough resources to exert.
				if (!sourcePlayer.CanPlay(sourceCard))
				{
					return false;
				}

				// Exert resources.
				int numExerted = 0;
				foreach (Card inkedCard in sourcePlayer.Inkwell)
				{
					if (inkedCard.IsReady)
					{
						inkedCard.IsReady = false;
						numExerted += 1;
						if (numExerted >= sourceCard.Cost)
						{
							break;
						}
					}
				}

				// Move card from the player's hand to the field.
				sourcePlayer.Hand.Remove(sourceCard);
				sourcePlayer.Field.Add(sourceCard);
				
			}
			else if (turnAction.type == TurnAction.Type.UseAbility)
			{
				Card sourceCard = turnAction.SourceCard;
				string abilityName = turnAction.AbilityName;

				// Lookup the ability and use it.
				string lookupKey = sourceCard.Name + "_" + sourceCard.Version + "_" + abilityName;
				Abilities[lookupKey](turnAction);
			}
			else if (turnAction.type == TurnAction.Type.ChallengeCard)
			{
				Player sourcePlayer = turnAction.SourcePlayer;
				Card sourceCard = turnAction.SourceCard;
				Player targetPlayer = turnAction.TargetPlayer;
				Card targetCard = turnAction.TargetCard;

				// Exert the card.
				sourceCard.IsReady = false;

				// Apply damage between the cards.
				sourceCard.DamageCounters += targetCard.Strength;
				targetCard.DamageCounters += sourceCard.Strength;

				// Remove from respective player's boards if DamageCounters >= Willpower
				if (sourceCard.DamageCounters >= sourceCard.Willpower)
				{
					sourcePlayer.Field.Remove(sourceCard);
					sourcePlayer.Discard.Add(sourceCard);
				}

				if (targetCard.DamageCounters >= targetCard.Willpower)
				{
					targetPlayer.Field.Remove(targetCard);
					targetPlayer.Discard.Add(targetCard);
				}

			}
			else if (turnAction.type == TurnAction.Type.InkCard)
			{
				Player sourcePlayer = turnAction.SourcePlayer;
				Card sourceCard = turnAction.SourceCard;

				// Check if the card can be inked.
				if (!sourceCard.Inkable)
				{
					return false;
				}

				sourcePlayer.Hand.Remove(sourceCard);
				sourcePlayer.Inkwell.Add(sourceCard);

			}
			else if (turnAction.type == TurnAction.Type.QuestCard)
			{
				Player sourcePlayer = turnAction.SourcePlayer;
				Card sourceCard = turnAction.SourceCard;

				// Check if it's a ready character.
				if (sourceCard.CardType != CardType.Character || !sourceCard.IsReady)
				{
					return false;
				}

				// Exert the character.
				sourceCard.IsReady = false;

				sourcePlayer.LoreTotal += sourceCard.Lore;

				// TODO: some way to signal that the player won.

			}


			return true;

		}

	}
	
}
