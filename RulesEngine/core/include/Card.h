#pragma once

#include <json/json.h>

#include <string>
#include <vector>


namespace Lorcana
{

// Enums
enum class CardType
{
    Character,
    Action,
    Item,
    Location,
    Song
};

enum class Classification
{
    Ally,
    Villain,
    Hero,
    Alien,
    Dreamborn,
    Storyborn,
    Floodborn
};

enum class Rarity
{
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

class Card
{
public:
    // Main attributes.
    uint8_t cost;
    std::string name;
    std::string version;
    CardType cardType;
    std::vector<Classification> classifications;
    uint8_t strength;
    uint8_t willpower;
    uint8_t lore;
    bool inkable;
    std::string cardText;
    Rarity rarity;
    uint8_t damageCounters;
    bool isReady;
    bool isDry = false;

    // Other attributes.
    bool canReady = true;

    Card() = default;
    ~Card() = default;
    Card(const Card& other) = default;

    Card(const Json::Value& jsonValue);
};

}  // namespace Lorcana
