export module day:day10;

import :base;
import std;
import common;

export class Day10 : public Day
{
public:
	Day10() : Day(10) {}

private:
	std::string part1() override;
	std::string part2() override;
	void prepare_input() override;

	Matrix<char> m_input;
	std::pair<int, int> m_start;
};