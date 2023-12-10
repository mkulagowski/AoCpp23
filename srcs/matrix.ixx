export module common:matrix;

import std;

export {
	enum Direction {
		DOWN_LEFT,
		DOWN,
		DOWN_RIGHT,
		RIGHT,
		UP_RIGHT,
		UP,
		UP_LEFT,
		LEFT
	};

	std::pair<int, int> to_coords(Direction dir) {
		switch (dir) {
			case DOWN_LEFT: return {-1, 1};
			case DOWN: return {0, 1};
			case DOWN_RIGHT: return {1, 1};
			case RIGHT: return {1, 0};
			case UP_RIGHT: return {1, -1};
			case UP: return {0, -1};
			case UP_LEFT: return {-1, -1};
			case LEFT: return {-1, 0};
		}

		return {0, 0};
	}

	template<typename T>
	class Matrix
	{
	public:
		std::vector<T> m_data;

		Matrix(size_t rows, size_t cols, T value)
			: m_data(rows * cols, value)
            , m_rows(rows),
            m_cols(cols) {}

		Matrix() : Matrix(0, 0, 0) {}
		
		size_t rows() const {
			return m_rows;
		}

		size_t cols() const {
			return m_cols;
		}

		void init(size_t rows, size_t cols, T value) {
			m_rows = rows;
			m_cols = cols;
			m_data = std::vector<T>(rows * cols, value);
		}

		void init(size_t rows, size_t cols, const std::vector<std::vector<T>>& vals) {
			m_rows = rows;
			m_cols = cols;
			m_data.resize(rows * cols);
			set_data(vals);
		}

		inline T& get(size_t x, size_t y) {
			return m_data[x + y * m_cols];
		}

		inline void set(size_t x, size_t y, T val) {
			get(x, y) = val;
		}

		inline void set_data(const std::vector<std::vector<T>>& vals) {
			for (int y = 0; y < vals.size(); y++) {
				// Could speed-up by memcping the whole row
				for (int x = 0; x < vals[0].size(); x++) {
					set(x, y, vals[y][x]);
				}
			}
		}

		inline bool is_valid(int xx, int yy) {
			return xx >= 0 && xx < m_cols && yy >= 0 && yy < m_rows;
		}

		template<typename F>
		void process_neighbours(int x, int y, F&& functor, bool include_diags = true) {
			constexpr std::array<std::tuple<Direction, int, int>, 8> W_DIAGS = {{ {UP_LEFT, -1, -1}, {UP, 0, -1}, {UP_RIGHT, 1, -1}, {LEFT, -1, 0}, {RIGHT, 1, 0}, {DOWN_LEFT, -1, 1}, {DOWN, 0, 1}, {DOWN_RIGHT, 1, 1} }};
			constexpr std::array<std::tuple<Direction, int, int>, 8> WO_DIAGS = {{ {UP, 0, -1}, {LEFT, -1, 0}, {RIGHT, 1, 0}, {DOWN, 0, 1} }};

			const auto& coords = include_diags ? W_DIAGS : WO_DIAGS;
			for (const auto& [dir, dx, dy] : coords) {
				const int xx = x + dx;
				const int yy = y + dy;

				if (!is_valid(xx, yy))
					continue;

				functor(xx, yy, dir);
			}
		}

		void print(bool with_spaces = false) {
			for (int y = 0; y < m_rows; y++) {
				for (int x = 0; x < m_cols; x++) {
					std::cout << get(x, y);
					if (with_spaces) std::cout << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}

	private:
		size_t m_rows, m_cols;
	};
}