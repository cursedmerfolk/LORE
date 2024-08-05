#pragma once

#include <json/json.h>

#include <iostream>
#include <regex>
#include <string>
#include <vector>


namespace Redacted
{

class Player;

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

    Card(Player* owner_) : owner(owner_) {};

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

    bool ApplyDamage(int8_t damageAmount);

    bool ChangeZone(std::vector<Card>& from, std::vector<Card>& to, int8_t index = -1);

    /* Initialize values like hasEvasive, hasRush, etc. */
    bool parseCardText();

    // Main attributes.
    uint8_t cost;
    std::string fullName;
    std::string baseName;
    std::string version;
    CardType cardType;
    std::vector<Classification> classifications;
    union  // strength for Characters, moveCost for Locations
    {
        uint8_t strength;
        uint8_t moveCost;
    };
    uint8_t willpower;
    uint8_t lore;
    bool inkable;
    std::vector<std::string> abilitiesText;
    Rarity rarity;
    CardColor color;
    Card* atLocation;
    Player* owner;

    // Other attributes.
    // Note - these must be initialized to avoid undefined behavior.
    uint8_t damageCounters{0}; 
    uint8_t resistValue{0};
    uint8_t singerValue{0};     // Defaults to card cost.
    uint8_t shiftValue{0};
    uint8_t index{0};           // index in it's current zone.
    bool isReady{true};
    bool isDry{false};
    bool canReadyThisTurn{true};
    bool canQuestThisTurn{true};
    bool isVisible{true};
    bool hasRush{false};
    bool hasEvasive{false};
    bool hasWard{false};
    bool hasBodyguard{false};
    bool hasShift{false};

};

}  // namespace Redacted
