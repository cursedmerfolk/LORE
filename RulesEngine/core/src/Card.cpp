#include "Card.h"

namespace Lorcana {

    Card::Card(const Json::Value& jsonValue)
    {
        cost = jsonValue["cost"].asInt();
        name = jsonValue["fullName"].asString();
        version = jsonValue["code"].asString();
        cardType = getCardType(jsonValue["type"].asString());

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

    CardType getCardType(const std::string& typeStr) {
        if (typeStr == "Character") return CardType::Character;
        if (typeStr == "Action") return CardType::Action;
        if (typeStr == "Item") return CardType::Item;
        if (typeStr == "Location") return CardType::Location;
        if (typeStr == "Song") return CardType::Song;
        throw std::invalid_argument("Invalid card type");
    }

    Classification getClassification(const std::string& classStr) {
        if (classStr == "Ally") return Classification::Ally;
        if (classStr == "Villain") return Classification::Villain;
        if (classStr == "Hero") return Classification::Hero;
        if (classStr == "Alien") return Classification::Alien;
        if (classStr == "Dreamborn") return Classification::Dreamborn;
        if (classStr == "Storyborn") return Classification::Storyborn;
        if (classStr == "Floodborn") return Classification::Floodborn;
        throw std::invalid_argument("Invalid classification");
    }

    Rarity getRarity(const std::string& rarityStr) {
        if (rarityStr == "Common") return Rarity::Common;
        if (rarityStr == "Uncommon") return Rarity::Uncommon;
        if (rarityStr == "Rare") return Rarity::Rare;
        if (rarityStr == "SuperRare") return Rarity::SuperRare;
        if (rarityStr == "Legendary") return Rarity::Legendary;
        if (rarityStr == "Enchanted") return Rarity::Enchanted;
        throw std::invalid_argument("Invalid rarity");
    }

}