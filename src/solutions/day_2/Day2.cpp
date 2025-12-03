#include "Day2.h"

#include <algorithm>
#include <ranges>
#include <vector>

#include "../../utils/EmbeddedFile.h"


std::string aoc::day_2::part_1() noexcept
{
	long long total = 0;

	for (const auto& line : utils::embedded_file::embedded_input_by_line(utils::embedded_file::day_2_input_arr, COMMA_CHAR))
	{
		const size_t separator_index = line.find(HYPHEN_CHAR);
		const long long lower_int = std::stoll(line.substr(0, separator_index));
		const long long upper_int = std::stoll(line.substr(separator_index + 1));

		for (long long i = lower_int; i <= upper_int; ++i)
		{
			std::string product_id = std::to_string(i);

			if (product_id.length() % 2 != 0)
			{
				continue;
			}

			size_t half_index = product_id.length() >> 1;

			std::string left_half  = product_id.substr(0, half_index);
			std::string right_half = product_id.substr(half_index);

			total = left_half == right_half ? total + i : total;
		}
	}
	
	return std::to_string(total);
}

std::string aoc::day_2::part_2() noexcept
{
	long long total = 0;

	for (const auto& line : utils::embedded_file::embedded_input_by_line(utils::embedded_file::day_2_input_arr, COMMA_CHAR))
	{
		const size_t separator_index = line.find(HYPHEN_CHAR);
		const long long lower_int = std::stoll(line.substr(0, separator_index));
		const long long upper_int = std::stoll(line.substr(separator_index + 1));

		for (long long i = lower_int; i <= upper_int; ++i)
		{
			std::string product_id = std::to_string(i);

			size_t half_index = product_id.length() >> 1;

			for (size_t j = half_index; j > 0; --j)
			{
				auto chunk_view = product_id | std::views::chunk(j);

				if (
					const auto& first_chunk = *chunk_view.begin(); std::ranges::all_of(
						chunk_view, [&first_chunk](const auto& current_chunk) { return std::ranges::equal(current_chunk, first_chunk); })
				)
				{
					total += i;
					break;
				}
			}
		}
	}
	return std::to_string(total);
}