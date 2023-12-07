module day:day06;

import std;

static std::uint64_t find_min_time(std::uint64_t minn, std::uint64_t maxx, std::uint64_t val) {
	std::uint64_t min = minn;
	std::uint64_t max = maxx;
	while (min < max) {
		std::uint64_t curr = min + (max - min) / 2;
		std::uint64_t curr_val = (maxx - curr) * curr;
		if (curr_val == val) {
			return curr;
		} else if (curr_val < val) {
			min = curr + 1;
		} else {
			max = curr;
		}
	}

	return min;
}

static std::uint64_t calc_ways(std::uint64_t first, std::uint64_t total) {
	std::uint64_t half = total / 2;
	return (half - first + 1) * 2 + (total & 0x1 ? 0 : -1);
}

std::string Day06::part1() {
	std::uint64_t prod = 1;
	for (const Race& r : m_input) {
		std::uint64_t beg = find_min_time(0, r.time, r.distance + 1);
		prod *= calc_ways(beg, r.time);
	}
	return std::to_string(prod);
}

std::string Day06::part2() {
	std::uint64_t beg = find_min_time(0, m_ultimate_race.time, m_ultimate_race.distance + 1);
	return std::to_string(calc_ways(beg, m_ultimate_race.time));
}

void Day06::prepare_input() {
    auto input = get_day_input();
	std::string_view times = input[0];
	std::string_view dists = input[1];

	times.remove_prefix(5);
	dists.remove_prefix(9);

	auto times_v = split(times, ' ');
	auto dists_v = split(dists, ' ');
	std::string time = "", dist = "";

	for (int i = 0; i < times_v.size(); i++) {
		m_input.push_back({to_int<std::uint64_t>(times_v[i]), to_int<std::uint64_t>(dists_v[i])});
		time += times_v[i];
		dist += dists_v[i];
	}

	m_ultimate_race = {std::stoull(time), std::stoull(dist)};
}