export module day:day03;

import :base;
import common;
import std;

export class Day03 : public Day
{
public:
	Day03() : Day(3) {}

private:
	std::string part1() override;
	std::string part2() override;
	void prepare_input() override;

	Matrix<int> m_input;
	std::vector<int> m_nums;
	std::vector<char> m_symbols;
};