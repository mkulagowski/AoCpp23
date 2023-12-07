export module day:day01;

import :base;
import std;

export class Day01 : public Day
{
public:
	Day01() : Day(01) {}

private:
	std::string part1() override;
	std::string part2() override;

	void prepare_input() override
	{
		m_input = get_day_input();
	};


	std::vector<std::string> m_input;
};