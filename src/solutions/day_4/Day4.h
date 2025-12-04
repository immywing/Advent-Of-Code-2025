#ifndef DAY4_H
#define DAY4_H
#include <string>
#include <vector>

namespace aoc::day_4
{

	struct Cell
	{
		int row;
		int col;

		Cell(const int& row, const int& col);
	};

	bool is_out_of_bounds(const Cell& cell, const int& row_size, const int& col_size);
	long long count_adjacent_paper(const std::vector<std::string>& grid, const int& row, const int& col, const int& row_size, const int& col_size);

	constexpr int  MAX_ADJACENT = 3;
	constexpr char PAPER = '@';
	constexpr char DOT = '.';

	std::string part_1() noexcept;
	std::string part_2() noexcept;
}
#endif