#include "Player.h"

namespace Lorcana
{

uint8_t Player::currentId = 0;

bool Player::DoTurnStart(bool doDraw)
{
    // Ready phase.
    for (Card& card : field)
    {
        DoReadyPhase(card);
    }
    for (Card& card : inkwell)
    {
        DoReadyPhase(card);
    }

    // Set phase.
    for (Card& card : field)
    {
        DoSetPhase(card);
    }

    // Misc.
    inkedThisTurn = false;

    // Draw phase.
    if (doDraw)
    {
        hand.push_back(deck.back());
        deck.pop_back();
    }

    return true;
}

bool Player::CanPlay(const Card& card)
{
    auto readyInk = filterBy(inkwell, &Card::isReady, true);

    if (card.cost > readyInk.size())
    {
        return false;
    }

    return true;
}

bool Player::DoReadyPhase(Card& card)
{
    // TODO: these need moved up a level, game.currentPhase needs to be set to main afterwards.
    // TODO: Effects that would end "at the start of your turn" and "at the start of your next turn" end.

    if (card.canReady)
    {
        card.isReady = true;
    }

    return true;
}

bool Player::DoSetPhase(Card& card)
{
    card.isDry = true;

    // Gain lore from locations.
    if (card.cardType == CardType::Location)
    {
        loreTotal += card.lore;
    }

    // TODO: Add start of turn effects to the bag.

    // Misc.
    card.canReady = true;

    return true;
}

bool Player::DrawCards(uint8_t numCards = 1)
{
    // TODO: handle drawing more cards than the deck has.

    for (uint8_t i = 0; i < numCards; ++i)
    {
        hand.push_back(deck.back());
        deck.pop_back();
    }

    return true;
}

}  // namespace Lorcana
