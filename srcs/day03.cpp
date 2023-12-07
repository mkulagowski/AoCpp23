module day:day03;

import common;

import std;

std::string Day03::part1() {
	std::vector<bool> are_parts(m_nums.size(), false);
	std::uint64_t sum = 0;

	for (int y = 0; y < m_input.cols(); y++) {
		for (int x = 0; x < m_input.rows(); x++) {
			const int c = m_input.get(x, y);
			const bool is_symbol = c < 0;
			if (is_symbol) {
				m_input.process_neighbours(x, y, [&](int xx, int yy) {
					const int neigh = m_input.get(xx, yy);
					if (neigh > 0 && !are_parts[neigh - 1]) {
						are_parts[neigh - 1] = true;
						sum += m_nums[neigh - 1];
					}
				});
			}
			
		}
	}

	return std::to_string(sum);
}

std::string Day03::part2() {
	std::set<int> neigh_idxs;
	std::uint64_t sum = 0;

	for (int y = 0; y < m_input.cols(); y++) {
		for (int x = 0; x < m_input.rows(); x++) {
			const int c = m_input.get(x, y);
			const bool is_star = c < 0 && m_symbols[(- 1 * c) - 1] == '*';
			if (is_star) {
				neigh_idxs.clear();
				m_input.process_neighbours(x, y, [&](int xx, int yy) {
					const int neigh = m_input.get(xx, yy);
					if (neigh > 0) {
						neigh_idxs.insert(neigh - 1);
					}
				});

				if (neigh_idxs.size() == 2) {
					int power = 1;
					for (auto i : neigh_idxs) power *= m_nums[i];
					sum += power;
				}
			}
		}
	}

	return std::to_string(sum);
}

static inline bool is_num(char c)
{
	return c >= '0' && c <= '9';
}

static inline bool is_sym(char c)
{
	return !is_num(c) && c != '.';
}

void Day03::prepare_input() {
	auto input = get_day_input();
	const size_t cols = input.size();
	const size_t rows = input.front().size();
	m_input.init(rows, cols, 0);

	for (int y = 0; y < cols; y++) {
		int curr_num = 0;
		for (int x = 0; x < rows; x++) {
			const char c = input[y][x];
			if (is_num(c)) {
				curr_num = 10 * curr_num + (c - '0');
				m_input.set(x, y, static_cast<int>(m_nums.size()) + 1); // before push_back, start from idx 1
			} else {
				if (curr_num) {
					m_nums.push_back(curr_num);
					curr_num = 0;
				}

				if (is_sym(c)) {
					m_symbols.push_back(c);
					m_input.set(x, y, -1 * static_cast<int>(m_symbols.size())); // after push_back, start from idx 1
				}
			}
		}
		// case when line ends with num
		if (curr_num) {
			m_nums.push_back(curr_num);
		}
	}
}