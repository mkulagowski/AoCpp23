export module day:day09;

import :base;
import std;
import common;

export class Day09 : public Day
{
public:
	Day09() : Day(9) {}

private:
	std::string part1() override;
	std::string part2() override;
	void prepare_input() override;

	std::vector<std::vector<int>> m_histories;
};