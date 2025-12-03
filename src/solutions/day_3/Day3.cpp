#include "Day3.h"

#include <algorithm>
#include <iostream>
#include <ranges>
#include <set>
#include <utility>
#include <vector>

#include "../../utils/EmbeddedFile.h"


aoc::day_3::Battery::Battery(const int& value, const int& index) : value(value), index(index) {}

aoc::day_3::Battery aoc::day_3::pair_to_battery(const std::pair<char, int>& pair)
{
	return { pair.second - ZERO_CHAR, pair.first };
}

std::string aoc::day_3::part_1() noexcept
{
	int total = 0;

	for (const auto& line : utils::embedded_file::embedded_input_by_line(utils::embedded_file::day_3_input_arr))
	{
		int battery_1 = 0;
		size_t battery_1_index = 0;
		int battery_2 = 0;

		for (size_t i = 0; i < line.length() - 1; ++i)
		{
			int value = line[i] - ZERO_CHAR;
			if (value > battery_1)
			{
				battery_1 = value;
				battery_1_index = i;
			}
		}

		for (size_t i = battery_1_index + 1; i < line.length(); ++i)
		{
			int value = line[i] - ZERO_CHAR;
			battery_2 = std::max(value, battery_2);
		}

		std::string voltage = std::to_string(battery_1) + std::to_string(battery_2);
		total += std::stoi(voltage);

	}

	return std::to_string(total);
}

std::string aoc::day_3::part_2() noexcept
{
	long long total = 0;

	for (const auto& line : utils::embedded_file::embedded_input_by_line(utils::embedded_file::day_3_input_arr))
	{
		std::string voltage;
		int max_index = -1;

		auto battery_indexers = line |
			std::views::enumerate |
			std::views::transform(pair_to_battery) |
			std::ranges::to<std::vector<Battery>>();

		for (size_t window_size = TWELVE; window_size > 0; --window_size)
		{
			Battery max_battery(0, -1);

			for (const auto&& window : battery_indexers | std::views::slide(window_size) | std::views::reverse)
			{
				max_battery = window.front().value >= max_battery.value && window.front().index > max_index ? window.front() : max_battery;
			}

			max_index = max_battery.index;
			voltage.push_back(static_cast<char>(max_battery.value + ZERO_CHAR));
		}

		total += std::stoll(voltage);
	}

	return std::to_string(total);
}