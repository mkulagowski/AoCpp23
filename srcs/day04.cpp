module day:day04;

import std;
import common;

std::string Day04::part1() {
	std::uint64_t res = 0;
	for (const auto& cs : m_input) {
		const int power = (1 << cs.get_wins()) >> 1;
		res += power;
	}
	return std::to_string(res);
}

std::string Day04::part2() {
	std::vector<int> counters(m_input.size(), 1);

	for (int i = 0; i < counters.size(); i++) {
		const int count = counters[i];

		auto cs = m_input[i];
		int wins = cs.get_wins();

		for (int j = i + 1; j < i + 1 + wins && j < counters.size(); j++)
			counters[j] += count;
	}
	uint64_t res = 0;
	for (int n : counters) res += n;
	return std::to_string(res);
}

void Day04::prepare_input() {
	for (const auto& line : get_day_input()) {
		const auto split_off = line.find(':') + 1;
		std::string_view sv = line;
		sv.remove_prefix(split_off);
		const auto [winnings, cards] = split_once(sv, '|');

		CardSet cs;
		for (auto c : split(winnings, ' ')) {
			cs.winning_nums.insert(to_int(c));
		}
		for (auto c : split(cards, ' ')) {
			cs.card_nums.push_back(to_int(c));
		}
		m_input.push_back(cs);
	}
}