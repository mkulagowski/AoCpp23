module day:day07;

import std;

static std::uint64_t calc_total_winnings(const std::vector<Day07::Bid>& arr) {
	std::uint64_t result = 0;
	for (int i = 0; i < arr.size(); i++) {
		const auto& bid = arr[i];
		result += static_cast<std::uint64_t>(bid.value) * (i + 1);
	}
	return result;
}

std::string Day07::part1() {
	std::sort(m_input.begin(), m_input.end());
	return std::to_string(calc_total_winnings(m_input));
}

std::string Day07::part2() {
	std::sort(m_input_jokers.begin(), m_input_jokers.end());
	return std::to_string(calc_total_winnings(m_input_jokers));
}

void Day07::prepare_input() {
    auto input = get_day_input();
	for (std::string_view line : input) {
		const auto [hand_sv, bid_sv] = split_once(line, ' ');
		int bid = to_int(bid_sv);
		m_input.emplace_back(hand_sv, bid);
		m_input_jokers.emplace_back(hand_sv, bid, true);
	}
}