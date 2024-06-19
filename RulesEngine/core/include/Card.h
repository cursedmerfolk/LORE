#pragma once

#include <string>
#include <vector>

#include <json/json.h>

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

    CardType getCardType(const std::string& typeStr);
    Classification getClassification(const std::string& classStr);
    Rarity getRarity(const std::string& rarityStr);

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

        Card() = default;
        ~Card() = default;
        Card(const Card& other) = default;

        Card(const Json::Value& jsonValue);

    };

} // namespace Lorcana

