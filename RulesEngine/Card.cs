using System;
using System.Collections.Generic;

//[JsType(JsMode.Global, Filename="Card.js")]
namespace Lorcana
{

	// Idea: card has a Owner and Location rather than updating the Player data structures
	//  - not sure if this would work yet.

	public enum CardType
	{
		Character,
		Action,
		Item,
		Location,
		Song
	}

	public enum Classification
	{
		Ally,
		Villain,
		Hero,
		Alien,
		Dreamborn,
		Storyborn,
		Floodborn
	}

	public enum Rarity
	{
		Common,
		Uncommon,
		Rare,
		SuperRare,
		Legendary,
		Enchanted
	}

	public partial class Card
	{
		public int Cost { get; set; }
		public string Name { get; set; }
		public string Version { get; set; }
		public CardType CardType { get; set; }
		public List<Classification> Classifications { get; set; }
		public int Strength { get; set; }
		public int Willpower { get; set; }
		public int Lore { get; set; }
		public bool Inkable { get; set; }
		public string CardText { get; set; }
		public Rarity Rarity { get; set; }
		public int DamageCounters { get; set; } = 0;
		public bool IsReady { get; set; } = true;
		public bool IsDry { get; set; } = false;

	}

}
