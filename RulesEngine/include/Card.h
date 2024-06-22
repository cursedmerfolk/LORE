#pragma once

#include <json/json.h>

#include <iostream>
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
    */
    Card(const Card& other) : cost(other.cost),
                                fullName(other.fullName),
                                baseName(other.baseName),
                                version(other.version),
                                cardType(other.cardType),
                                classifications(other.classifications),
                                strength(other.strength),
                                willpower(other.willpower),
                                lore(other.lore),
                                inkable(other.inkable),
                                cardText(other.cardText),
                                rarity(other.rarity),
                                color(other.color) { };

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
    CardColor color;

    // Other attributes.
    // Note - these must be initialized to avoid undefined behavior.
    uint8_t damageCounters{0};
    bool isReady{true};
    bool isDry{false};
    bool canReady{true};
    bool isVisible{true};
};

}  // namespace Lorcana
