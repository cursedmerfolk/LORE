#pragma once

#include <string>
#include <vector>

namespace Lorcana {

    // Enums
    enum class CardType {
        Character,
        Action,
        Item,
        Location,
        Song
    };

    enum class Classification {
        Ally,
        Villain,
        Hero,
        Alien,
        Dreamborn,
        Storyborn,
        Floodborn
    };

    enum class Rarity {
        Common,
        Uncommon,
        Rare,
        SuperRare,
        Legendary,
        Enchanted
    };

    // Class definition
    class Card {
    public:
			 
        int cost;
        std::string name;
        std::string version;
        CardType cardType;
        std::vector<Classification> classifications;
        int strength;
        int willpower;
        int lore;
        bool inkable;
        std::string cardText;
        Rarity rarity;
        int damageCounters;
        bool isReady;
        bool isDry;

    };

} // namespace Lorcana

