#pragma once

#include <string>
#include <vector>

#include "Card.h"
#include "Util.h"

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
    bool inkedThisTurn{false};

    static uint8_t currentId;

    bool DoTurnStart(bool doDraw = true);
    bool DoTurnEnd();
    bool CanPlay(const Card& card);
    bool CanInk(const Card& card); 
    bool CanMove(const Card& character, const Card& location);  // TODO: not tested
    bool DoReadyPhase(Card& card);
    bool DoSetPhase(Card& card);
    bool DrawCards(uint8_t numCards);
};

}  // namespace Lorcana