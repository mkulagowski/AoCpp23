module day:base;

void Day::solve() {
	prepare_input();

	const auto begin_time = std::chrono::steady_clock::now();
	const auto res1 = part1();
    const auto mid_time = std::chrono::steady_clock::now();
	const auto res2 = part2();
	const auto end_time = std::chrono::steady_clock::now();

    const auto elapsed_p1 = std::chrono::duration_cast<std::chrono::microseconds>(mid_time - begin_time).count();
    const auto elapsed_p2 = std::chrono::duration_cast<std::chrono::microseconds>(end_time - mid_time).count();
    std::printf("D %02d] P1: \"%s\" (%lldus), P2: \"%s\" (%lldus)\n", m_day, res1.c_str(), elapsed_p1, res2.c_str(), elapsed_p2);
}

std::string Day::get_day_name(int day)
{
    std::ostringstream oss;
    oss << "day";
    oss << std::setw(2) << std::setfill('0') << day;
    return oss.str();
}

std::vector<std::string> Day::get_day_input()
{
    const std::string day_name = get_day_name(m_day);
    std::vector<std::string> lines;
    std::filesystem::path file_path("srcs/inputs/" + day_name + ".in");
    std::ifstream file(file_path);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
    }
    return lines;
}