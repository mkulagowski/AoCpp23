module day:day10;

import std;

static bool is_valid_connection_from(char c, Direction entry_dir) {
	static std::map<Direction, std::set<char>> valid_conns{
		{LEFT, {'-', 'L', 'F'}},
		{DOWN, {'|', 'L', 'J'}},
		{RIGHT, {'-', '7', 'J'}},
		{UP, {'|', '7', 'F'}},
	};

	return valid_conns[entry_dir].contains(c);
}

static Direction get_exit_dir(char c, Direction entry_dir) {
	static std::map<Direction, std::map<char, Direction>> mapping{
		{RIGHT, {{'-', RIGHT}, {'7', DOWN}, {'J', UP}}},
		{UP, {{'|', UP}, {'7', LEFT}, {'F', RIGHT}}},
		{LEFT, {{'-', LEFT}, {'F', DOWN}, {'L', UP}}},
		{DOWN, {{'|', DOWN}, {'J', LEFT}, {'L', RIGHT}}},
	};

	return mapping[entry_dir][c];
}

std::string Day10::part1() {
	std::unordered_map<int, std::unordered_set<int>> seen_coords;
	std::queue<std::tuple<Direction, int, int>> qq;
	m_input.process_neighbours(m_start.first, m_start.second, [&](int x, int y, Direction dir) {
		if (is_valid_connection_from(m_input.get(x, y), dir)) {
			qq.push({dir, x, y});
			seen_coords[x].insert(y);
		}
	}, false);

	seen_coords[m_start.first].insert(m_start.second);

	int steps = 0;
	while (!qq.empty()) {
		steps++;
		size_t step_len = qq.size();
		for (int i = 0; i < step_len; i++) {
			auto [entry_dir, x, y] = qq.front();
			qq.pop();

			auto exit_dir = get_exit_dir(m_input.get(x, y), entry_dir);
			auto [dx, dy] = to_coords(exit_dir);
			x += dx;
			y += dy;

			if (m_input.is_valid(x, y) && !(seen_coords.contains(x) && seen_coords[x].contains(y))) {
				qq.push({exit_dir, x, y});
				seen_coords[x].insert(y);
			}
		}
	}

	for (int y = 0; y < m_input.rows(); y++) {
		for (int x = 0; x < m_input.cols(); x++) {
			if ((!seen_coords.contains(x) || !seen_coords[x].contains(y))) {
				m_input.set(x, y, '.');
			}
		}
	}

	return std::to_string(steps);
}

std::string Day10::part2() {
	std::vector<Direction> start_dirs;
	m_input.process_neighbours(m_start.first, m_start.second, [&](int x, int y, Direction dir) {
		if (is_valid_connection_from(m_input.get(x, y), dir)) {
			start_dirs.push_back(dir);
		}
    }, false);

	static std::map<Direction, std::map<Direction, char>> start_pipe_mapping{
		{DOWN,  { {UP, '|'},   {LEFT, '7'}, {RIGHT, 'F'} }},
		{LEFT,  { {UP, 'J'},   {DOWN, '7'}, {RIGHT, '-'} }},
		{UP,    { {DOWN, '|'}, {LEFT, 'J'}, {RIGHT, 'L'} }},
		{RIGHT, { {UP, 'L'},   {LEFT, '-'}, {DOWN, 'F'} }},
	};

	m_input.set(m_start.first, m_start.second, start_pipe_mapping[start_dirs[0]][start_dirs[1]]);

	bool is_inside;
	int count = 0;
	char last_corner = 0;
	for (int y = 0; y < m_input.rows(); y++) {
		is_inside = false;
		for (int x = 0; x < m_input.cols(); x++) {
			const char c = m_input.get(x, y);
			switch (c) {
				case '.': 
					count += is_inside;
					break;
				case 'F':
				case 'L':
					last_corner = c;
					break;
				case 'J':
					is_inside ^= last_corner == 'F';
					last_corner = 0;
					break;
				case '7':
					is_inside ^= last_corner == 'L';
					last_corner = 0;
					break;
				case '|':
					is_inside ^= true;
					break;
			}
		}
	}
	return std::to_string(count);
}

void Day10::prepare_input() {
    auto input = get_day_input();
	m_input.init(input.size(), input.front().size(), '.');

	for (int y = 0; y < input.size(); y++) {
		for (int x = 0; x < input.front().size(); x++) {
			const char val = input[y][x];
			m_input.set(x, y, val);
			if (val == 'S') {
				m_start = {x, y};
			}
		}
	}
}