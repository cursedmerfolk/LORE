#include "Player.h"

namespace Redacted
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

bool Player::DoTurnEnd()
{
    for (Card& card : field)
    {
        card.canQuestThisTurn = true;
    }

    return true;
}

bool Player::CanPlay(const Card& card)
{
    auto const& readyInk = filterBy(inkwell, &Card::isReady, true);

    // If the card has shift and there is available ink, check for a shift target.
    // TODO: not tested.
    if (card.hasShift && card.shiftValue <= readyInk.size())
    {
        // Find cards on the field with the same base name as this card.
        const auto& shiftTargets = filterBy(field, &Card::baseName, card.baseName);

        // If there is at least one shift target, the card can be played.
        if (!shiftTargets.empty())
        {
            return true;
        }
    }

    if (card.cost > readyInk.size())
    {
        return false;
    }

    return true;
}

bool Player::CanInk(const Card& card)
{
    if (inkedThisTurn)
    {
        return false;
    }

    if (!card.inkable)
    {
        return false;
    }

    return true;
}

bool Player::CanMove(const Card& character, const Card& location)
{
    auto const& readyInk = filterBy(inkwell, &Card::isReady, true);

    if (location.strength > readyInk.size())
    {
        return false;
    }

    return true;
}

bool Player::DoReadyPhase(Card& card)
{
    // TODO: these need moved up a level, game.currentPhase needs to be set to main afterwards.
    // TODO: Effects that would end "at the start of your turn" and "at the start of your next turn" end.

    if (card.canReadyThisTurn)
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
    card.canReadyThisTurn = true;

    return true;
}

bool Player::DrawCards(uint8_t numCards = 1)
{
    for (uint8_t i = 0; i < numCards; ++i)
    {
        if (deck.empty())
        {
            return false;
        }

        hand.push_back(deck.back());
        deck.pop_back();
    }

    return true;
}

}  // namespace Redacted
