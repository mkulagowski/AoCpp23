export module day:day08;

import :base;
import std;
import common;

export class Day08 : public Day
{
public:
	Day08() : Day(8) {}

	enum Direction {
		LEFT,
		RIGHT
	};

private:
	std::string part1() override;
	std::string part2() override;
	void prepare_input() override;

	int calc_steps(int start, bool p2);

	std::vector<Direction> m_navigation;
	std::unordered_map<std::string, int> m_node_mapping;
	std::vector<std::array<int, 2>> m_network;
	int m_start, m_end;
	std::set<int> m_start_nodes;
	std::set<int> m_end_nodes;
};