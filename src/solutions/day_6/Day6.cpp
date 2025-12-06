#include "Day6.h"

#include <algorithm>
#include <ranges>

#include "../../utils/EmbeddedFile.h"

std::string aoc::day_6::part_1() noexcept
{
	long long total = 0;

	const auto lines = utils::embedded_file::embedded_input_by_line(utils::embedded_file::day_6_input_arr);

	const auto split_string_by_whitespace_lambda = [](const std::string& line)
		{
			return line
				| std::views::split(SPACE_CHAR)
				| std::views::transform([](auto&& subrange) { return std::string(subrange.begin(), subrange.end()); })
				| std::views::filter([](const std::string& s) { return !s.empty(); })
				| std::ranges::to<std::vector>();
		};

	const auto lines_split_by_column = lines
		| std::views::transform(split_string_by_whitespace_lambda)
		| std::ranges::to<std::vector>();

	for (size_t col = 0; col < lines_split_by_column.front().size(); ++col)
	{
		const auto operator_str = lines_split_by_column.back().at(col);

		auto numbers = lines_split_by_column
			| std::views::take(lines_split_by_column.size() - 1)
			| std::views::transform([&col](const auto& v) { return std::stoll(v.at(col)); })
			| std::ranges::to<std::vector>();

		total += operator_str == MULTIPLY_SIGN
			? std::ranges::fold_left(numbers, 1LL, std::multiplies())
			: std::ranges::fold_left(numbers, 0LL, std::plus());
	}

	return std::to_string(total);
}

std::string aoc::day_6::part_2() noexcept
{
	long long total = 0;

	auto lines = utils::embedded_file::embedded_input_by_line(utils::embedded_file::day_6_input_arr);

	const auto operators = lines.back()
		| std::views::split(SPACE_CHAR)
		| std::views::transform([](auto&& subrange) { return std::string(subrange.begin(), subrange.end()); })
		| std::views::filter([](const std::string& s) { return !s.empty(); })
		| std::ranges::to<std::vector>();

	lines.pop_back();

	/* transformation lambdas  */ 
	const auto lambda_transform_to_vertical_lines = [&lines](const size_t& index)
		{
			return lines
				| std::views::transform([&index](const auto& s) { return s.at(index); })
				| std::ranges::to<std::string>();
		};

	const auto lambda_subrange_to_long_long = [](const auto&& subrange)
		{
			return std::vector(subrange.begin(), subrange.end())
				| std::views::transform([](const std::string& s) { return std::stoll(s); })
				| std::ranges::to<std::vector>();
		};

	const auto vertical_lines = std::views::iota(static_cast<size_t>(0),lines.front().size())
		| std::views::transform(lambda_transform_to_vertical_lines)
		| std::ranges::to<std::vector>();

	const auto calculations = vertical_lines
		| std::views::split(std::string(vertical_lines.front().size(), SPACE_CHAR))
		| std::views::transform(lambda_subrange_to_long_long)
		| std::ranges::to<std::vector>();

	auto operator_it = operators.begin();

	for (const auto& vec: calculations)
	{
		total += *operator_it == MULTIPLY_SIGN
			? std::ranges::fold_left(vec, 1LL, std::multiplies())
			: std::ranges::fold_left(vec, 0LL, std::plus());

		operator_it = std::next(operator_it);
	}

	return std::to_string(total);
}
