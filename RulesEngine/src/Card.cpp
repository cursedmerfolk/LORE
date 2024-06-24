#include "Card.h"

namespace Lorcana
{

Card::Card(const Card& other) : cost(other.cost),
                                fullName(other.fullName),
                                baseName(other.baseName),
                                version(other.version),
                                cardType(other.cardType),
                                classifications(other.classifications),
                                strength(other.strength),
                                willpower(other.willpower),
                                lore(other.lore),
                                inkable(other.inkable),
                                abilitiesText(other.abilitiesText),
                                rarity(other.rarity),
                                color(other.color)
{
    parseCardText();
};

Card::Card(const Json::Value& jsonValue)
{
    cost = jsonValue["cost"].asInt();
    fullName = jsonValue["fullName"].asString();
    baseName = jsonValue["baseName"].asString();
    version = jsonValue["subtitle"].asString();
    cardType = getCardType(jsonValue["type"].asString());

    for (const auto& subtype : jsonValue["subtypes"])
    {
        classifications.push_back(getClassification(subtype.asString()));
    }

    strength = jsonValue["strength"].asInt();
    willpower = jsonValue["willpower"].asInt();
    lore = jsonValue["lore"].asInt();
    inkable = jsonValue["inkwell"].asBool();
    for (const auto& ability : jsonValue["abilities"])
    {
        abilitiesText.push_back(ability.asString());
    }
    rarity = getRarity(jsonValue["rarity"].asString());
    color = getColor(jsonValue["color"].asString());

    parseCardText();
}

// TODO: move this to a script that will create some sort of config that's loaded, so that it's faster.
bool Card::parseCardText()
{
    // singerValue defaults to card cost.
    singerValue = cost;

    std::smatch match;

    for (std::string& abilityText : abilitiesText)
    {
        std::regex re("^Rush ");
        if (std::regex_search(abilityText, match, re))
        {
            hasRush = true;
        }

        re = std::regex("^Evasive ");
        if (std::regex_search(abilityText, match, re))
        {
            hasEvasive = true;
        }

        re = std::regex("^Ward ");
        if (std::regex_search(abilityText, match, re))
        {
            hasWard = true;
        }

        re = std::regex("^Support ");
        if (std::regex_search(abilityText, match, re))
        {
            // TODO: not sure how 'whenever character quests' abilities are going to work yet.
        }

        re = std::regex("^Bodyguard ");
        if (std::regex_search(abilityText, match, re))
        {
            // TODO: may need a 'whenever you play character' ability.
            hasBodyguard = true;
        }

        // Check for Resist +N
        re = std::regex("^Resist \\+(\\d+)");
        if (std::regex_search(abilityText, match, re))
        {
            resistValue = std::stoi(match[1]);
        }

        // Check for Singer N
        re = std::regex("^Singer (\\d+) ");
        if (std::regex_search(abilityText, match, re))
        {
            singerValue = std::stoi(match[1]);
        }

        // Check for Shift N
        re = std::regex("^Shift (\\d+) ");
        if (std::regex_search(abilityText, match, re))
        {
            hasShift = true;
            shiftValue = std::stoi(match[1]);
        }
    }

    return true;
}

bool Card::ApplyDamage(int8_t damageAmount)
{
    // resistValue defaults to 0.
    damageAmount -= resistValue;

    // Damage can't be negative.
    if (damageAmount < 0)
    {
        damageAmount = 0;
    }

    damageCounters += damageAmount;

    return true;
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

CardColor getColor(const std::string& colorStr)
{
    if (colorStr == "Amber") return CardColor::Amber;
    if (colorStr == "Amethyst") return CardColor::Amethyst;
    if (colorStr == "Emerald") return CardColor::Emerald;
    if (colorStr == "Ruby") return CardColor::Ruby;
    if (colorStr == "Sapphire") return CardColor::Sapphire;
    if (colorStr == "Steel") return CardColor::Steel;
    if (colorStr == "") return CardColor::Unknown;
    throw std::invalid_argument("Invalid color: " + colorStr);
}

}  // namespace Lorcana