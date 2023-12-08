export module day:day04;

import :base;
import std;

export class Day04 : public Day
{
public:
	Day04() : Day(4) {}

	struct CardSet {
		std::unordered_set<int> winning_nums;
		std::vector<int> card_nums;

		int get_wins() const {
			int wins = 0;
			for (auto n : card_nums)
				if (winning_nums.contains(n)) wins++;
			return wins;
		}
	};
private:
	std::string part1() override;
	std::string part2() override;
	void prepare_input() override;

	std::vector<CardSet> m_input;
};