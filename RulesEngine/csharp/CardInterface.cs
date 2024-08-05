using System.Collections.Generic;

namespace LORE
{
    public interface ICard
    {
        public LORE_Player GetOwner()
        {
            return Game.Cards[this].owner;
        }

        public void SetOwner(LORE_Player value)
        {
            Game.Cards[this].owner = value;
        }

        public byte GetCost()
        {
            return Game.Cards[this].cost;
        }

        public void SetCost(byte value)
        {
            Game.Cards[this].cost = value;
        }

        public string GetFullName()
        {
            return Game.Cards[this].fullName;
        }

        public void SetFullName(string value)
        {
            Game.Cards[this].fullName = value;
        }

        public string GetBaseName()
        {
            return Game.Cards[this].baseName;
        }

        public void SetBaseName(string value)
        {
            Game.Cards[this].baseName = value;
        }

        public string GetVersion()
        {
            return Game.Cards[this].version;
        }

        public void SetVersion(string value)
        {
            Game.Cards[this].version = value;
        }

        public CardType GetCardType()
        {
            return Game.Cards[this].cardType;
        }

        public void SetCardType(CardType value)
        {
            Game.Cards[this].cardType = value;
        }

        // public List<Classification> GetClassifications()
        // {
        //     return Game.Cards[this].classifications;
        // }

        // public void SetClassifications(List<Classification> value)
        // {
        //     Game.Cards[this].classifications = value;
        // }

        public byte GetStrength()
        {
            return Game.Cards[this].strength;
        }

        public void SetStrength(byte value)
        {
            Game.Cards[this].strength = value;
        }

        public byte GetMoveCost()
        {
            return Game.Cards[this].moveCost;
        }

        public void SetMoveCost(byte value)
        {
            Game.Cards[this].moveCost = value;
        }

        public byte GetWillpower()
        {
            return Game.Cards[this].willpower;
        }

        public void SetWillpower(byte value)
        {
            Game.Cards[this].willpower = value;
        }

        public byte GetLore()
        {
            return Game.Cards[this].lore;
        }

        public void SetLore(byte value)
        {
            Game.Cards[this].lore = value;
        }

        public bool GetInkable()
        {
            return Game.Cards[this].inkable;
        }

        public void SetInkable(bool value)
        {
            Game.Cards[this].inkable = value;
        }

        // public List<string> GetAbilitiesText()
        // {
        //     return Game.Cards[this].abilitiesText;
        // }

        // public void SetAbilitiesText(List<string> value)
        // {
        //     Game.Cards[this].abilitiesText = value;
        // }

        public Rarity GetRarity()
        {
            return Game.Cards[this].rarity;
        }

        public void SetRarity(Rarity value)
        {
            Game.Cards[this].rarity = value;
        }

        public CardColor GetColor()
        {
            return Game.Cards[this].color;
        }

        public void SetColor(CardColor value)
        {
            Game.Cards[this].color = value;
        }

        // public Card GetAtLocation()
        // {
        //     return Game.Cards[this].atLocation;
        // }

        // public void SetAtLocation(Card value)
        // {
        //     Game.Cards[this].atLocation = value;
        // }
    }
}

