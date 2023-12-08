module day:day08;

import std;

int Day08::calc_steps(int start, bool p2) {
	int nav_counter = 0;
	int current_node = start;
	int steps = 0;

	auto check = [&](int node) {
		if (p2) {
			return m_end_nodes.contains(node);
		}
		return node == m_end;
	};

	while (!check(current_node)) {
		const auto dir = m_navigation[nav_counter];
		nav_counter = (nav_counter + 1) % m_navigation.size();

		current_node = m_network[current_node][dir];
		steps++;
	}
	return steps;
}

std::string Day08::part1() {
	return std::to_string(calc_steps(m_start, false));
}

std::string Day08::part2() {
	int nav_counter = 0;
	std::vector<int> current_nodes(m_start_nodes.begin(), m_start_nodes.end());
	std::vector<int> steps;

	for (int n : current_nodes) {
		steps.push_back(calc_steps(n, true));
	}

	std::uint64_t res = 1;
	for (auto n : steps)
		res  = std::lcm(res, n);
	
	return std::to_string(res);
}

void Day08::prepare_input() {
    auto input = get_day_input();

	for (char c : input[0]) {
		if (c == 'L')
			m_navigation.push_back(LEFT);
		else if (c == 'R')
			m_navigation.push_back(RIGHT);
	}

	for (int i = 2; i < input.size(); i++) {
		std::string_view sv = input[i];
		auto [from, to] = split_once(sv, " = ");
		to.remove_prefix(1);
		to.remove_suffix(1);
		auto [left, right] = split_once(to, ", ");
		const std::string from_s(from);
		const std::string left_s(left);
		const std::string right_s(right);


		if (!m_node_mapping.contains(from_s)) {
			m_node_mapping[from_s] = static_cast<int>(m_node_mapping.size());
		}
		if (!m_node_mapping.contains(left_s)) {
			m_node_mapping[left_s] = static_cast<int>(m_node_mapping.size());
		}
		if (!m_node_mapping.contains(right_s)) {
			m_node_mapping[right_s] = static_cast<int>(m_node_mapping.size());
		}

		m_network.resize(m_node_mapping.size() + 1);
		m_network[m_node_mapping[from_s]] = {m_node_mapping[left_s], m_node_mapping[right_s]};

		if (from_s.compare("AAA") == 0) {
			m_start = m_node_mapping[from_s];
		}
		if (from_s.compare("ZZZ") == 0) {
			m_end = m_node_mapping[from_s];
		}

		if (from_s[2] == 'A')
			m_start_nodes.insert(m_node_mapping[from_s]);
		if (from_s[2] == 'Z')
			m_end_nodes.insert(m_node_mapping[from_s]);
	}
}