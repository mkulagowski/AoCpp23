export module day:day06;

import :base;
import std;
import common;

export class Day06 : public Day
{
public:
	Day06() : Day(06) {}

	struct Race {
		std::uint64_t time;
		std::uint64_t distance;

		Race() : Race(0, 0) {}
		Race(std::uint64_t t, std::uint64_t d) : time(t), distance(d) {}
	};


private:
	std::string part1() override;
	std::string part2() override;
	void prepare_input() override;

	std::vector<Race> m_input;
	Race m_ultimate_race;
};