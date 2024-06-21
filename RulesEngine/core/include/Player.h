#pragma once

#include <string>
#include <vector>

#include "Card.h"

namespace Lorcana
{

class Player
{
public:
    Player() = default;
    ~Player() = default;
    Player(const Player& other) = default;

    Player(const std::string& name_) : name(name_), id(Player::currentId++) {}

    uint8_t id;
    uint8_t loreTotal{0};
    std::string name;
    std::vector<Card> hand;
    std::vector<Card> field;
    std::vector<Card> discard;
    std::vector<Card> deck;
    std::vector<Card> inkwell;

    // Misc
    bool doneMulligan{false};

    static uint8_t currentId;

    bool TurnStart();
    bool CanPlay(const Card& card);
    bool DoReadyPhase(Card& card);
    bool DoSetPhase(Card& card);
};

}  // namespace Lorcana