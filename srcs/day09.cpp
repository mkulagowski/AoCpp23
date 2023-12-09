module day:day09;

import std;

std::string Day09::part1() {
	std::int64_t sum = 0;
	for (const auto& history : m_histories) {
		std::vector<int> last_elems;
		std::vector<int> curr = history;
		bool all_zeros = false;
		while (!all_zeros) {
			last_elems.push_back(curr.back());
			std::vector<int> new_diff;
			new_diff.reserve(curr.size() - 1);
			all_zeros = true;
			for (int i = 1; i < curr.size(); i++) {
				const int num = curr[i] - curr[i - 1];
				new_diff.push_back(num);
				all_zeros &= num == 0;
			}
			std::swap(new_diff, curr);
		}

		for (int& n : last_elems) {
			sum += n;
		}
	}
	return std::to_string(sum);
}

std::string Day09::part2() {
	std::int64_t sum = 0;
	for (const auto& history : m_histories) {
		std::vector<int> first_elems;
		std::vector<int> curr = history;
		bool all_zeros = false;
		while (!all_zeros) {
			first_elems.push_back(curr.front());
			std::vector<int> new_diff;
			new_diff.reserve(curr.size() - 1);
			all_zeros = true;
			for (int i = 1; i < curr.size(); i++) {
				const int num = curr[i] - curr[i - 1];
				new_diff.push_back(num);
				all_zeros &= num == 0;
			}
			std::swap(new_diff, curr);
		}

		int pred = 0;
		for (int i = static_cast<int>(first_elems.size()) - 1; i >= 0; i--) {
			pred = first_elems[i] - pred;
		}
		sum += pred;
	}
	return std::to_string(sum);
}

void Day09::prepare_input() {
	for (std::string_view line : get_day_input()) {
		m_histories.push_back({});
		for (auto& num : split(line, ' ')) {
			m_histories.back().push_back(to_int(num));
		}
	}
}