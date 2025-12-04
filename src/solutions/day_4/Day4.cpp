#include "Day4.h"

#include <algorithm>
#include <ranges>

#include "../../utils/EmbeddedFile.h"

aoc::day_4::Cell::Cell(const int& row, const int& col) : row(row), col(col) {}

bool aoc::day_4::is_out_of_bounds(const Cell& cell, const int& row_size, const int& col_size)
{
	return (cell.row < 0 || cell.row >= row_size) || (cell.col < 0 || cell.col >= col_size);
}

long long aoc::day_4::count_adjacent_paper(const std::vector<std::string>& grid, const int& row, const int& col, const int& row_size, const int& col_size)
{
	std::vector adjacent_cells =
	{
		Cell(row - 1, col - 1),
		Cell(row - 1, col),
		Cell(row - 1, col + 1),
		Cell(row, col - 1),
		Cell(row, col + 1),
		Cell(row + 1, col - 1),
		Cell(row + 1, col),
		Cell(row + 1, col + 1),
	};

	std::erase_if(adjacent_cells, [&row_size, &col_size](const Cell& cell) {return is_out_of_bounds(cell, row_size, col_size); });

	auto adjacent_chars = adjacent_cells
		| std::views::transform([&grid](const Cell& c) { return grid[c.row][c.col]; })
		| std::ranges::to<std::vector<char>>();

	return std::ranges::count(adjacent_chars, PAPER);
}

std::string aoc::day_4::part_1() noexcept
{
	int total = 0;

	auto lines = utils::embedded_file::embedded_input_by_line(utils::embedded_file::day_4_input_arr);

	/* Assumption: symmetrical 2D grid */
	const int row_size = static_cast<int>(lines.size());
	const int col_size = static_cast<int>(lines.front().size());

	for (int row = 0; row < row_size; ++row)
	{
		for (int col = 0; col < col_size; ++col)
		{
			if (lines[row][col] == PAPER)
			{
				const auto adjacent_count = count_adjacent_paper(lines, row, col, row_size, col_size);
				total = adjacent_count <= MAX_ADJACENT ? total + 1 : total;
			}
		}
	}

	return std::to_string(total);
}

std::string aoc::day_4::part_2() noexcept
{
	int total = 0;

	auto lines = utils::embedded_file::embedded_input_by_line(utils::embedded_file::day_4_input_arr);

	/* Assumption: symmetrical 2D grid */
	const int row_size = static_cast<int>(lines.size());
	const int col_size = static_cast<int>(lines.front().size());

	auto lambda_contains_paper = [](const std::string& s) { return s.find(PAPER) != std::string::npos; };
	bool change_made = true;

	while (std::ranges::any_of(lines, lambda_contains_paper) && change_made)
	{
		change_made = false;
		std::vector<Cell> removed_paper;

		for (int row = 0; row < row_size; ++row)
		{
			for (int col = 0; col < col_size; ++col)
			{
				if (lines[row][col] == PAPER)
				{
					if (const auto& adjacent_count = count_adjacent_paper(lines, row, col, row_size, col_size); adjacent_count <= MAX_ADJACENT)
					{
						
						change_made = true;
						/* Changing in place during iteration did work for my input, but not sure if the entire grid should be assessed -> changed -> acted upon again? */
						//total++;
						//lines[row][col] = '.'; 
						removed_paper.emplace_back(row, col);
					}
				}
			}
		}

		total += static_cast<int>(removed_paper.size());

		for (const auto& cell : removed_paper)
		{
			lines[cell.row][cell.col] = DOT;
		}

	}

	return std::to_string(total);
}
