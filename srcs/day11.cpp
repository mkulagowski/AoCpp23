module day:day11;

import std;


void Day11::expand_galaxies(int empty_multiplier) {
	int counter = 0;
	for (int y = 0; y < m_empty_rows.size(); y++) {
		if (m_empty_rows[y]) {
			counter++;
		} else {
			for (auto& galaxy : m_rows_to_galaxy[y]) {
				galaxy->y += counter * (empty_multiplier - 1);
			}
		}

	}
	
	counter = 0;
	for (int x = 0; x < m_empty_cols.size(); x++) {
		if (m_empty_cols[x]) {
			counter++;
		} else {
			for (auto& galaxy : m_cols_to_galaxy[x]) {
				galaxy->x += counter * (empty_multiplier - 1);
			}
		}

	}
}


std::string Day11::part1() {
	expand_galaxies(2);

	std::uint64_t total_dist = 0;
	for (int i = 0; i < m_galaxies.size(); i++) {
		for (int j = i + 1; j < m_galaxies.size(); j++) {
			auto& g1 = m_galaxies[i];
			auto& g2 = m_galaxies[j];
			total_dist += std::abs(g1->x - g2->x) + std::abs(g1->y - g2->y);
		}
	}
	return std::to_string(total_dist);
}

std::string Day11::part2() {
	expand_galaxies(1000000 - 1);

	std::uint64_t total_dist = 0;
	for (int i = 0; i < m_galaxies.size(); i++) {
		for (int j = i + 1; j < m_galaxies.size(); j++) {
			auto& g1 = m_galaxies[i];
			auto& g2 = m_galaxies[j];
			total_dist += std::abs(g1->x - g2->x) + std::abs(g1->y - g2->y);
		}
	}
	return std::to_string(total_dist);
}

void Day11::prepare_input() {
    auto input = get_day_input();
	m_empty_rows.resize(input.size(), true);
	m_empty_cols.resize(input.front().size(), true);
	for (int y = 0; y < input.size(); y++) {
		for (int x = 0; x < input.front().size(); x++) {
			const char c = input[y][x];
			if (c == '#') {
				m_empty_rows[y] = false;
				m_empty_cols[x] = false;
				auto galaxy = std::make_shared<Galaxy>(x, y);
				m_galaxies.push_back(galaxy);
				m_cols_to_galaxy[x].push_back(galaxy);
				m_rows_to_galaxy[y].push_back(galaxy);
			}
		}
	}
}