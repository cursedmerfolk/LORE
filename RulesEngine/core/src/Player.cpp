#include "Player.h"

namespace Lorcana
{

uint8_t Player::currentId = 0;

bool Player::TurnStart()
{
    // Ready phase.
    for (Card& card : field)
    {
        DoReadyPhase(card);
    }

    // Set phase.
    for (Card& card : field)
    {
        DoSetPhase(card);
    }

    // Draw phase.
    hand.push_back(deck.back());
    deck.pop_back();

    return true;
}

bool Player::CanPlay(const Card& card)
{
    int numReadyInk = 0;
    for (const Card& inkedCard : inkwell)
    {
        if (inkedCard.isReady)
        {
            numReadyInk += 1;
        }
    }

    // 	// TODO: enable once Inkwell is implemented.
    // 	// if (card.Cost > numReadyInk) {
    // 	//     return false;
    // 	// }

    return true;
}

bool Player::DoReadyPhase(Card& card)
{
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

    //
    card.canReady = true;

    return true;
}

}  // namespace Lorcana
