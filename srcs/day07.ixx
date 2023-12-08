export module day:day07;

import :base;
import std;
import common;

export class Day07 : public Day
{
public:
	Day07() : Day(7) {}

	struct Hand {
		enum Type {
			NONE,
			HIGH_CARD,
			PAIR,
			TWO_PAIR,
			THREE_OF_KIND,
			FULL_HOUSE,
			FOUR_OF_KIND,
			FIVE_OF_KIND,
		};

		std::array<std::uint8_t, 5> hand_order;
		std::array<std::uint8_t, 13> counter;
		Type type;

		Hand() : type(NONE) {}

		Hand(std::string_view hand_sv, bool jokers_included = false) : Hand() {
			counter.fill(0);
			for (int i = 0; i < hand_sv.size(); i++) {
				const int hand_idx = card_to_idx(hand_sv[i], jokers_included);
				hand_order[i] = hand_idx;
				counter[hand_idx]++;
			}

			int high_card = -1;
			for (int card = (jokers_included ? 1 : 0); card < counter.size(); card++) {
				const std::uint8_t quantity = counter[card];
				if (quantity) {
					high_card = card;
				}

				if (quantity == 5) {
					type = FIVE_OF_KIND;
					break;
				} else if (quantity == 4) {
					type = FOUR_OF_KIND;
					break;
				} else if (quantity == 3) {
					if (type == PAIR) {
						type = FULL_HOUSE;
						break;
					} else {
						type = THREE_OF_KIND;
					}
				} else if (quantity == 2) {
					if (type == THREE_OF_KIND) {
						type = FULL_HOUSE;
						break;
					} else if (type == PAIR) {
						type = TWO_PAIR;
						break;
					} else {
						type = PAIR;
					}
				}
			}

			if (jokers_included) {
				const std::uint8_t jokers = counter[0];
				if (jokers) {
					switch (type) {
						case FOUR_OF_KIND:
							type = FIVE_OF_KIND;
							break;
						case THREE_OF_KIND:
							if (jokers == 1)
								type = FOUR_OF_KIND;
							else
								type = FIVE_OF_KIND;
							break;
						case TWO_PAIR:
							type = FULL_HOUSE;
							break;
						case PAIR:
							if (jokers == 1)
								type = THREE_OF_KIND;
							else if (jokers == 2)
								type = FOUR_OF_KIND;
							else
								type = FIVE_OF_KIND;
							break;
						case NONE:
							if (jokers == 1)
								type = PAIR;
							else if (jokers == 2)
								type = THREE_OF_KIND;
							else if (jokers == 3)
								type = FOUR_OF_KIND;
							else
								type = FIVE_OF_KIND;
							break;
					}
				}
			}

			if (type == NONE) {
				type = HIGH_CARD;
			}
		}

		bool operator<(const Hand& other) {
			if (type == other.type) {
				for (int i = 0; i < hand_order.size(); i++) {
					auto hand_subres = hand_order[i] <=> other.hand_order[i];
					if (hand_order[i] == other.hand_order[i])
						continue;
					return hand_order[i] < other.hand_order[i];
				}
			}
			return type < other.type;
		}

		int card_to_idx(char c, bool jokers_included) {
			switch (c) {
				case 'A': return 12;
				case 'K': return 11;
				case 'Q': return 10;
				case 'J': return jokers_included ? 0 : 9;
				case 'T': return jokers_included ? 9 : 8;
				default:
					return c - (jokers_included ? '1' : '2');
			}
		}
	};

	struct Bid {
		Hand hand;
		int value;

		Bid(std::string_view hand_str, int val, bool joker_rules = false) : hand(hand_str, joker_rules), value(val) {}

		bool operator<(const Bid& other) {
			return hand < other.hand;
		}
	};

private:
	std::string part1() override;
	std::string part2() override;
	void prepare_input() override;

	std::vector<Bid> m_input;
	std::vector<Bid> m_input_jokers;
};