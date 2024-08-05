using System.Collections.Generic;

namespace LORE
{
    public interface IPlayer
    {
        byte GetId()
        {
            return Game.Players[this].id;
        }
        void SetId(byte value)
        {
            Game.Players[this].id = value;
        }

        byte GetLoreTotal()
        {
            return Game.Players[this].loreTotal;
        }
        void SetLoreTotal(byte value)
        {
            Game.Players[this].loreTotal = value;
        }

        string GetName()
        {
            return Game.Players[this].name;
        }
        void SetName(string value)
        {
            Game.Players[this].name = value;
        }

        // List<LORE_Card> GetHand()
        // {
        //     return Game.Players[this].hand;
        // }
        // void SetHand(List<LORE_Card> value)
        // {
        //     Game.Players[this].hand = value;
        // }

        // List<LORE_Card> GetField()
        // {
        //     return Game.Players[this].field;
        // }
        // void SetField(List<LORE_Card> value)
        // {
        //     Game.Players[this].field = value;
        // }

        // List<LORE_Card> GetDiscard()
        // {
        //     return Game.Players[this].discard;
        // }
        // void SetDiscard(List<LORE_Card> value)
        // {
        //     Game.Players[this].discard = value;
        // }

        // List<LORE_Card> GetDeck()
        // {
        //     return Game.Players[this].deck;
        // }
        // void SetDeck(List<LORE_Card> value)
        // {
        //     Game.Players[this].deck = value;
        // }

        // List<LORE_Card> GetInkwell()
        // {
        //     return Game.Players[this].inkwell;
        // }
        // void SetInkwell(List<LORE_Card> value)
        // {
        //     Game.Players[this].inkwell = value;
        // }

        bool GetDoneMulligan()
        {
            return Game.Players[this].doneMulligan;
        }
        void SetDoneMulligan(bool value)
        {
            Game.Players[this].doneMulligan = value;
        }

        bool GetInkedThisTurn()
        {
            return Game.Players[this].inkedThisTurn;
        }
        void SetInkedThisTurn(bool value)
        {
            Game.Players[this].inkedThisTurn = value;
        }
    }
}
