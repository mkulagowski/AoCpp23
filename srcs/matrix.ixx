export module common:matrix;

import std;

export {
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

		inline T& get(size_t x, size_t y) {
			return m_data[x + y * m_rows];
		}

		inline void set(size_t x, size_t y, T val) {
			get(x, y) = val;
		}

		template<typename F>
		void process_neighbours(int x, int y, F&& functor, bool include_diags = true) {
			constexpr std::array<std::pair<int, int>, 8> W_DIAGS = {{ {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1} }};
			constexpr std::array<std::pair<int, int>, 8> WO_DIAGS = {{ {0, -1}, {-1, 0}, {1, 0}, {0, 1} }};

			const auto& coords = include_diags ? W_DIAGS : WO_DIAGS;
			for (const auto& [dx, dy] : coords) {
				const int xx = x + dx;
				const int yy = y + dy;

				if (xx < 0 || xx >= m_rows || yy < 0 || yy >= m_cols)
					continue;

				functor(xx, yy);
			}
		}

	private:
		size_t m_rows, m_cols;
	};
}