export module day:base;

import std;

export class Day
{
public:
	Day(int n) : m_day(n) {}
	void solve();
	
protected:
	static std::string get_day_name(int day);
	std::vector<std::string> get_day_input();
	int m_day = 0;

private:
	virtual void prepare_input() = 0;
	virtual std::string part1() = 0;
	virtual std::string part2() = 0;
};