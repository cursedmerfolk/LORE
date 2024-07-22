using System.Collections.Generic;


namespace LORE {

public interface CardInterface {

	public LORE_Player Owner
	{
		get {
			return Game.Cards[this].owner;
		}
		set {
			Game.Cards[this].owner = value;
		}
	}
   

	public byte Cost
	{
		get
		{
			return Game.Cards[this].cost;
		}
		set
		{
			Game.Cards[this].cost = value;
		}
	}

	public string FullName
	{
		get
		{
			return Game.Cards[this].fullName;
		}
		set
		{
			Game.Cards[this].fullName = value;
		}
	}

	public string BaseName
	{
		get
		{
			return Game.Cards[this].baseName;
		}
		set
		{
			Game.Cards[this].baseName = value;
		}
	}

	public string Version
	{
		get
		{
			return Game.Cards[this].version;
		}
		set
		{
			Game.Cards[this].version = value;
		}
	}

	public CardType CardType
	{
		get
		{
			return Game.Cards[this].cardType;
		}
		set
		{
			Game.Cards[this].cardType = value;
		}
	}

	public List<Classification> Classifications
	{
		get
		{
			return Game.Cards[this].classifications;
		}
		set
		{
			Game.Cards[this].classifications = value;
		}
	}

	public byte Strength
	{
		get
		{
			return Game.Cards[this].strength;
		}
		set
		{
			Game.Cards[this].strength = value;
		}
	}

	public byte MoveCost
	{
		get
		{
			return Game.Cards[this].moveCost;
		}
		set
		{
			Game.Cards[this].moveCost = value;
		}
	}

	public byte Willpower
	{
		get
		{
			return Game.Cards[this].willpower;
		}
		set
		{
			Game.Cards[this].willpower = value;
		}
	}

	public byte Lore
	{
		get
		{
			return Game.Cards[this].lore;
		}
		set
		{
			Game.Cards[this].lore = value;
		}
	}

	public bool Inkable
	{
		get
		{
			return Game.Cards[this].inkable;
		}
		set
		{
			Game.Cards[this].inkable = value;
		}
	}

	public List<string> AbilitiesText
	{
		get
		{
			return Game.Cards[this].abilitiesText;
		}
		set
		{
			Game.Cards[this].abilitiesText = value;
		}
	}

	public Rarity Rarity
	{
		get
		{
			return Game.Cards[this].rarity;
		}
		set
		{
			Game.Cards[this].rarity = value;
		}
	}

	public CardColor Color
	{
		get
		{
			return Game.Cards[this].color;
		}
		set
		{
			Game.Cards[this].color = value;
		}
	}

	// TODO: fix
	// public Card AtLocation
	// {
	// 	get
	// 	{
	// 		return Game.Cards[Game.Cards[this].atLocation];
	// 	}
		// set
		// {
		// 	Game.Cards[this].atLocation = value;
		// }
	// }

}

} // Namespace LORE
