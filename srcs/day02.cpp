module day:day02;

import std;

static bool is_game_possible(Day02::CubeSet set)
{
	constexpr Day02::CubeSet REF{12, 13, 14};
	return set.red <= REF.red
		&& set.green <= REF.green
		&& set.blue <= REF.blue;
}

static Day02::CubeSet get_max(Day02::CubeSet set, Day02::CubeSet other)
{
	return Day02::CubeSet{
		std::max(set.red, other.red),
		std::max(set.green, other.green),
	    std::max(set.blue, other.blue)
	};
}

std::string Day02::part1()
{
	std::uint64_t sum = 0;
	for (int g_idx = 0; g_idx < m_input.size(); g_idx++) {
		bool is_possible = true;
		for (const auto game_set : m_input[g_idx])
		{
			is_possible &= is_game_possible(game_set);
		}
		sum += is_possible * (g_idx + 1);
	}
	return std::to_string(sum);
}

std::string Day02::part2() {
	std::uint64_t sum = 0;

	for (const auto& game : m_input)
	{
		CubeSet min_set;
		for (const auto game_set : game) {
			min_set = get_max(min_set, game_set);
		}
		sum += min_set.get_power();
	}
	return std::to_string(sum);
}

void Day02::prepare_input() {
	std::regex set_rx("(\\d+) (red|blue|green)");
	for (const auto& line : get_day_input()) {
		size_t curr_off = line.find(':') + 1;
		Game g;
		while (true)
		{
			const auto split_off = line.find(';', curr_off);
			CubeSet set;
			auto from = line.begin() + curr_off;
			auto to = [&]() {
				if (split_off == std::string::npos)
					return line.end();
				else
					return line.begin() + split_off;
				}();
			auto words_begin = std::sregex_iterator(from, to, set_rx);
			auto words_end = std::sregex_iterator();

			for (std::sregex_iterator i = words_begin; i != words_end; ++i)
			{
				std::smatch sm = *i;
				if (sm[2].str()[0] == 'r')
				{
					set.red = std::stoi(sm[1].str());
				}
				else if (sm[2].str()[0] == 'g')
				{
					set.green = std::stoi(sm[1].str());
				}
				else if (sm[2].str()[0] == 'b')
				{
					set.blue = std::stoi(sm[1].str());
				}
			}
			g.push_back(set);

			if (split_off == std::string::npos) break;
			curr_off = split_off + 1;
		}

		m_input.push_back(g);
	}
};