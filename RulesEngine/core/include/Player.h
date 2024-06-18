#pragma once

#include <vector>
#include <string>

#include "Card.h"


namespace Lorcana {
	
	class Player {
	public:
		Player() = default;
		~Player() = default;
		Player(const Player& other) = default;

		Player(const std::string& name_) : name(name_) {}

		std::string name;
		std::vector<Card> hand;
		std::vector<Card> field;
		std::vector<Card> discard;
		int loreTotal = 0;
		std::vector<Card> deck;
		std::vector<Card> inkwell;

		bool canPlay(const Card& card) {
			int numReadyInk = 0;
			for (const Card& inkedCard : inkwell) {
				if (inkedCard.isReady) {
					numReadyInk += 1;
				}
			}

		// 	// TODO: enable once Inkwell is implemented.
		// 	// if (card.Cost > numReadyInk) {
		// 	//     return false;
		// 	// }

			return true;
		}
	};

} // namespace Lorcana