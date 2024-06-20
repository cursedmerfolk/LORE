#include "Card.h"

namespace Lorcana
{

Card::Card(const Json::Value& jsonValue)
{
    cost = jsonValue["cost"].asInt();
    name = jsonValue["fullName"].asString();
    version = jsonValue["code"].asString();
    cardType = getCardType(jsonValue["type"].asString());

    bool first = true;
    for (const auto& subtype : jsonValue["subtypes"])
    {
        classifications.push_back(getClassification(subtype.asString()));
    }

    strength = jsonValue["strength"].asInt();
    willpower = jsonValue["willpower"].asInt();
    lore = jsonValue["lore"].asInt();
    inkable = jsonValue["inkwell"].asBool();
    cardText = jsonValue["fullText"].asString();
    rarity = getRarity(jsonValue["rarity"].asString());
}

CardType getCardType(const std::string& typeStr)
{
    if (typeStr == "Character") return CardType::Character;
    if (typeStr == "Action") return CardType::Action;
    if (typeStr == "Item") return CardType::Item;
    if (typeStr == "Location") return CardType::Location;
    throw std::invalid_argument("Invalid card type: " + typeStr);
}

Classification getClassification(const std::string& classStr)
{
    if (classStr == "Inventor") return Classification::Inventor;
    if (classStr == "Hyena") return Classification::Hyena;
    if (classStr == "Detective") return Classification::Detective;
    if (classStr == "Knight") return Classification::Knight;
    if (classStr == "Captain") return Classification::Captain;
    if (classStr == "Song") return Classification::Song;
    if (classStr == "Deity") return Classification::Deity;
    if (classStr == "Queen") return Classification::Queen;
    if (classStr == "Princess") return Classification::Princess;
    if (classStr == "Madrigal") return Classification::Madrigal;
    if (classStr == "Musketeer") return Classification::Musketeer;
    if (classStr == "Sorcerer") return Classification::Sorcerer;
    if (classStr == "Seven Dwarfs") return Classification::Seven_Dwarfs;
    if (classStr == "Tigger") return Classification::Tigger;
    if (classStr == "Dragon") return Classification::Dragon;
    if (classStr == "Pirate") return Classification::Pirate;
    if (classStr == "Puppy") return Classification::Puppy;
    if (classStr == "Titan") return Classification::Titan;
    if (classStr == "Fairy") return Classification::Fairy;
    if (classStr == "Broom") return Classification::Broom;
    if (classStr == "King") return Classification::King;
    if (classStr == "Prince") return Classification::Prince;
    if (classStr == "Mentor") return Classification::Mentor;
    if (classStr == "Entangled") return Classification::Entangled;
    if (classStr == "Ally") return Classification::Ally;
    if (classStr == "Villain") return Classification::Villain;
    if (classStr == "Hero") return Classification::Hero;
    if (classStr == "Alien") return Classification::Alien;
    if (classStr == "Dreamborn") return Classification::Dreamborn;
    if (classStr == "Storyborn") return Classification::Storyborn;
    if (classStr == "Floodborn") return Classification::Floodborn;
    throw std::invalid_argument("Invalid classification: " + classStr);
}

Rarity getRarity(const std::string& rarityStr)
{
    if (rarityStr == "Common") return Rarity::Common;
    if (rarityStr == "Uncommon") return Rarity::Uncommon;
    if (rarityStr == "Rare") return Rarity::Rare;
    if (rarityStr == "Super Rare") return Rarity::Super_Rare;
    if (rarityStr == "Legendary") return Rarity::Legendary;
    if (rarityStr == "Enchanted") return Rarity::Enchanted;
    if (rarityStr == "Special") return Rarity::Special;
    throw std::invalid_argument("Invalid rarity: " + rarityStr);
}

}  // namespace Lorcana