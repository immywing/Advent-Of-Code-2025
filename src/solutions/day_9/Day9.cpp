#include "Day9.h"

#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

#include "../../utils/EmbeddedFile.h"

bool aoc::day_9::line_intersects_bounds_box(const Vec2& a, const Vec2& b, const pair_pair_ll& line) noexcept
{
	const auto min_x = std::min(a.x, b.x);
	const auto max_x = std::max(a.x, b.x);
	const auto min_y = std::min(a.y, b.y);
	const auto max_y = std::max(a.y, b.y);

	if (line.first.x != line.second.x && line.first.y != line.second.y) return false;
	if (line.first.x == line.second.x && line.first.y == line.second.y) return false;

	if (line.first.y == line.second.y)
	{
		auto line_min_x = std::min(line.first.x, line.second.x);
		auto line_max_x = std::max(line.first.x, line.second.x);
		return (min_y < line.first.y && line.first.y < max_y) && ((line_min_x <= min_x && min_x < line_max_x) || (line_min_x < max_x && max_x <= line_max_x));
	}

	if (line.first.x == line.second.x)
	{
		auto line_min_y = std::min(line.first.y, line.second.y);
		auto line_max_y = std::max(line.first.y, line.second.y);
		return (min_x < line.first.x && line.first.x < max_x) && ((line_min_y <= min_y && min_y < line_max_y) || (line_min_y < max_y && max_y <= line_max_y));
	}

	return false;
}

std::string aoc::day_9::part_1() noexcept
{
	const auto lambda_split_string_by_comma = [](const std::string& line)
		{
			auto temp_vec = line
				| std::views::split(COMMA_CHAR)
				| std::views::transform([](auto&& subrange) { return std::stoll(std::string(subrange.begin(), subrange.end())); })
				| std::ranges::to<std::vector>();

			return Vec2{.x = temp_vec[0], .y = temp_vec[1] };
		};

	const auto lambda_to_area = [](const pair_pair_ll& pair_pair)
		{
			return (std::abs(pair_pair.first.x - pair_pair.second.x) + 1) * (std::abs(pair_pair.first.y - pair_pair.second.y) + 1);
		};

	const auto tile_coords = utils::embedded_file::embedded_input_by_line(utils::embedded_file::day_9_input_arr)
		| std::views::transform(lambda_split_string_by_comma)
		| std::ranges::to<std::vector>();

	auto cartesian_product_view = std::views::cartesian_product(tile_coords, tile_coords);

	std::vector<pair_pair_ll> cartesian_product(cartesian_product_view.begin(), cartesian_product_view.end());

	const long long max_area = std::ranges::max(cartesian_product | std::views::transform(lambda_to_area));

	return std::to_string(max_area);
}

std::string aoc::day_9::part_2() noexcept
{
	const auto lambda_split_string_by_comma = [](const std::string& line)
		{
			auto temp_vec = line
				| std::views::split(COMMA_CHAR)
				| std::views::transform([](auto&& subrange) { return std::stoll(std::string(subrange.begin(), subrange.end())); })
				| std::ranges::to<std::vector>();

			return Vec2{ .x = temp_vec[0], .y = temp_vec[1] };
		};

	const auto tile_coords = utils::embedded_file::embedded_input_by_line(utils::embedded_file::day_9_input_arr)
		| std::views::transform(lambda_split_string_by_comma)
		| std::ranges::to<std::vector>();

	auto cartesian_product_view = std::views::cartesian_product(tile_coords, tile_coords);

	std::vector<pair_pair_ll> cartesian_product(cartesian_product_view.begin(), cartesian_product_view.end());

	cartesian_product = cartesian_product
		| std::views::filter([](const auto& pair_pair) { return pair_pair.first != pair_pair.second ; })
		| std::ranges::to<std::vector>();

	const auto lambda_to_area = [&tile_coords](const pair_pair_ll& pair_pair)
		{
			auto no_intersections_with_rectangle =
				std::ranges::none_of(
					tile_coords | std::views::slide(2),
					[&pair_pair](const auto& elements) { return line_intersects_bounds_box(pair_pair.first, pair_pair.second, std::make_pair(elements[0], elements[1])); }
				) && !line_intersects_bounds_box(pair_pair.first, pair_pair.second, std::make_pair(tile_coords.front(), tile_coords.back()));

			return no_intersections_with_rectangle ? (std::abs(pair_pair.first.x - pair_pair.second.x) + 1) * (std::abs(pair_pair.first.y - pair_pair.second.y) + 1) : 0;
		};

	const long long max_area = std::ranges::max(cartesian_product | std::views::transform(lambda_to_area));

	return std::to_string(max_area);
}