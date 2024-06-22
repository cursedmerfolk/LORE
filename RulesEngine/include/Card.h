#pragma once

#include <json/json.h>

#include <iostream>
#include <string>
#include <vector>


namespace Lorcana
{

enum class CardType
{
    Character,
    Action,
    Item,
    Location,
};

enum class Classification
{
    Alien,
    Ally,
    Broom,
    Captain,
    Deity,
    Detective,
    Dragon,
    Dreamborn,
    Entangled,
    Fairy,
    Floodborn,
    Hero,
    Hyena,
    Inventor,
    King,
    Knight,
    Madrigal,
    Mentor,
    Musketeer,
    Pirate,
    Prince,
    Princess,
    Puppy,
    Queen,
    Seven_Dwarfs,
    Song,
    Sorcerer,
    Storyborn,
    Tigger,
    Titan,
    Villain,
};

enum class Rarity
{
    Common,
    Uncommon,
    Rare,
    Super_Rare,
    Legendary,
    Enchanted,
    Special,
};

CardType getCardType(const std::string& typeStr);
Classification getClassification(const std::string& classStr);
Rarity getRarity(const std::string& rarityStr);

class Card
{
public:
    Card() = default;
    ~Card() = default;
    Card(const Card& other) = default;

    Card(const Json::Value& jsonValue);

    // Main attributes.
    uint8_t cost;
    std::string fullName;
    std::string baseName;
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
    bool isReady{true};
    bool isDry{false};

    // Other attributes.
    bool canReady{true};
    bool isVisible{true};
};

}  // namespace Lorcana
