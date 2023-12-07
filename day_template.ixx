export module day:day[[NUM]];

import :base;
import std;

export class Day[[NUM]] : public Day
{
public:
	Day[[NUM]]() : Day([[NUM]]) {}

private:
	std::string part1() override;
	std::string part2() override;
	void prepare_input() override;

	std::vector<std::string> m_input;
};