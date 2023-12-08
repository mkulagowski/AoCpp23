export module day:day02;

import :base;
import std;

export class Day02 : public Day
{
public:
	Day02() : Day(2) {}

	struct CubeSet
	{
		int red = 0;
		int green = 0;
		int blue = 0;

		int get_power() const {
			return red * green * blue;
		}
	};

	using Game = std::vector<CubeSet>;

private:
	std::string part1() override;
	std::string part2() override;

	void prepare_input() override;


	std::vector<Game> m_input;
};