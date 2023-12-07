module day:day05;

import std;

std::string Day05::part1() {
	std::vector<std::uint64_t> vals = m_seeds;
	for (const auto& mapping : m_input) {
		for (auto& v : vals) {
			v = mapping.get(v);
		}
	}

	return std::to_string(*std::min_element(vals.begin(), vals.end()));
}

std::string Day05::part2() {
	std::vector<Range> ranges;
	for (int i = 0; i < m_seeds.size(); i += 2) {
		const auto from = m_seeds[i];
		const auto len = m_seeds[i + 1];
		ranges.emplace_back(from, len);
	}

	for (const auto& mapping : m_input) {
		std::vector<Range> new_ranges;
		for (auto& range : ranges) {
			const auto converted = mapping.get(range);
			new_ranges.reserve(new_ranges.size() + converted.size());
			new_ranges.insert(new_ranges.end(), converted.begin(), converted.end());
		}
		ranges = new_ranges;
	}

	std::uint64_t min_elem = ranges.front().start;
	for (const auto& r : ranges) min_elem = std::min(min_elem, r.start);

	return std::to_string(min_elem);
}

static inline bool is_num(char c) {
	return c >= '0' && c <= '9';
}

void Day05::prepare_input() {
    auto input = get_day_input();
	std::string_view seed_line = input[0];
	seed_line.remove_prefix(7);

	for (const auto seed : std::views::split(seed_line, ' ')) {
		m_seeds.push_back(to_int<std::uint64_t>(std::string_view(seed)));
	}

	//for (auto& seed : split_str(seed_line, ' ', 4)) {
	//	m_seeds.push_back(to_int<std::uint64_t>(seed));
	//}

	for (int i = 2; i < input.size(); i++) {
		const auto& line = input[i];
		if (line.empty())
			continue;

		if (is_num(line.front())) {
			auto vals = split(line, ' ', 3);
			const auto dst = to_int<std::uint64_t>(vals[0]);
			const auto src = to_int<std::uint64_t>(vals[1]);
			const auto len = to_int<std::uint64_t>(vals[2]);
			m_input.back().mappings.emplace(std::make_pair(src, Mapping{dst, src, len}));
		} else {
			m_input.resize(m_input.size() + 1);
		}
	}
}