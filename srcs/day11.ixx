export module day:day11;

import :base;
import std;
import common;

export class Day11 : public Day
{
public:
	Day11() : Day(11) {}

	struct Galaxy {
		int x, y;
	};

private:
	std::string part1() override;
	std::string part2() override;
	void prepare_input() override;

	void expand_galaxies(int empty_multiplier);

	std::vector<std::shared_ptr<Galaxy>> m_galaxies;
	std::unordered_map<int, std::vector<std::shared_ptr<Galaxy>>> m_rows_to_galaxy, m_cols_to_galaxy;
	std::vector<bool> m_empty_rows, m_empty_cols;
};