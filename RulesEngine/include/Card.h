#pragma once

#include <json/json.h>

#include <iostream>
#include <regex>
#include <string>
#include <vector>


namespace Lorcana
{

enum class CardColor
{
    Amber,
    Amethyst,
    Emerald,
    Sapphire,
    Steel,
    Ruby,
    Unknown,  // Ursula's Quest cards
};

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
    Special,  // Ursula's Quest cards
};

CardType getCardType(const std::string& typeStr);
Classification getClassification(const std::string& classStr);
Rarity getRarity(const std::string& rarityStr);
CardColor getColor(const std::string& colorStr);

class Card
{
public:
    Card() = default;
    ~Card() = default;

    /*
     * This constructor occurs specifically when a Card goes to a new zone.
     * When a card travels from one zone to another, it functionally becomes a new card.
     * 
     * Things like damageCounters, isReady, isDry etc get reset.
     * 
     * NOTE: vector.push_back() calls this constructor (unless you do std::move(), iirc).
    */
    Card(const Card& other);

    Card(const Json::Value& jsonValue);

    /* Initialize values like hasEvasive, hasRush, etc. */
    bool parseCardText();

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
    std::vector<std::string> abilitiesText;
    Rarity rarity;
    CardColor color;

    // Other attributes.
    // Note - these must be initialized to avoid undefined behavior.
    uint8_t damageCounters{0};
    uint8_t resistValue{0};
    bool isReady{true};
    bool isDry{false};
    bool canReady{true};
    bool isVisible{true};
    bool hasRush{false};
    bool hasEvasive{false};
    bool hasWard{false};

};

}  // namespace Lorcana
