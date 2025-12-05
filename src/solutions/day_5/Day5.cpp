#include "Day5.h"

#include <algorithm>
#include <ranges>

#include "../../utils/EmbeddedFile.h"

std::string aoc::day_5::part_1() noexcept
{
	int total = 0;

	const auto lines = utils::embedded_file::embedded_input_by_line(utils::embedded_file::day_5_input_arr);
	
	const auto empty_line_it = std::ranges::find(lines, "");

	const std::vector fresh_ingredient_ranges(lines.begin(), empty_line_it);
	const std::vector available_ingredients(empty_line_it + 1, lines.end());

	for (const auto& available_ingredient : available_ingredients)
	{
		for (const auto& fresh_range : fresh_ingredient_ranges)
		{
			const long long ingredient_id = std::stoll(available_ingredient);

			const size_t separator_index = fresh_range.find(HYPHEN_CHAR);
			const long long lower_int = std::stoll(fresh_range.substr(0, separator_index));
			const long long upper_int = std::stoll(fresh_range.substr(separator_index + 1));

			if (ingredient_id >= lower_int && ingredient_id <= upper_int)
			{
				total++;
				break;
			}
		}
	}

	return std::to_string(total);
}

std::string aoc::day_5::part_2() noexcept
{
	const auto lines = utils::embedded_file::embedded_input_by_line(utils::embedded_file::day_5_input_arr);

	const auto empty_line_it = std::ranges::find(lines, "");

	const std::vector fresh_ingredient_ranges(lines.begin(), empty_line_it);

	std::vector<std::pair<long long, long long>> ingredient_ranges;

	for (const auto& fresh_range : fresh_ingredient_ranges)
	{
		const size_t separator_index = fresh_range.find(HYPHEN_CHAR);
		const long long lower_int = std::stoll(fresh_range.substr(0, separator_index));
		const long long upper_int = std::stoll(fresh_range.substr(separator_index + 1));
		ingredient_ranges.emplace_back(lower_int, upper_int);
	}

	std::ranges::sort(ingredient_ranges, [](const auto& a, const auto& b) { return a.first < b.first; });

	for (auto it = ingredient_ranges.begin(); it != ingredient_ranges.end();)
	{
		for (auto next = std::next(it); next != ingredient_ranges.end();)
		{
			if (next->first <= it->second)
			{
				it->second = std::max(it->second, next->second);
				next = ingredient_ranges.erase(next);
				continue;
			}
			++next;
		}
		++it;
	}

	const long long total = std::ranges::fold_left(
		ingredient_ranges, 0LL,
		[](long long current_total, const auto& range) { return current_total + (range.second - range.first + 1); }
	);

	return std::to_string(total);
}