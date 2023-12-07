module day:day01;

import std;

static int get_calibration_value(std::string_view line)
{
	const auto front = line.find_first_of("0123456789");
	const auto back = line.find_last_of("0123456789");

	int res = 0;
	if (front != std::string::npos) {
		res += 10 * (line[front] - '0');
	}
	if (back != std::string::npos) {
		res += line[back] - '0';
	}

	return res;
}

static int convert_value_to_int(std::string_view val)
{
	if (val.size() == 1) {
		return val.front() - '0';
	}

	static std::unordered_map<std::string_view, int> val_mapping {
		{"one", 1},
		{"two", 2},
		{"three", 3},
		{"four", 4},
		{"five", 5},
		{"six", 6},
		{"seven", 7},
		{"eight", 8},
		{"nine", 9}
	};
	return val_mapping[val];
}

static int get_advanced_calibration_value(const std::string& line)
{
	const std::regex front_regex(".*?(\\d|one|two|three|four|five|six|seven|eight|nine)");
	const std::regex back_regex(".*(\\d|one|two|three|four|five|six|seven|eight|nine)");

	int res = 0;
	std::smatch match;
	if (std::regex_search(line, match, front_regex)) {
		res += 10 * convert_value_to_int(match.str(1));
	}
	if (std::regex_search(line, match, back_regex)) {
		res += convert_value_to_int(match.str(1));
	}

	return res;
}

std::string Day01::part1()
{
	std::uint64_t sum = 0;
	for (const auto& line : m_input) {
		sum += get_calibration_value(line);
	}
	return std::to_string(sum);
}

std::string Day01::part2() {
	std::uint64_t sum = 0;
	for (const auto& line : m_input)
	{
		sum += get_advanced_calibration_value(line);
	}
	return std::to_string(sum);
}