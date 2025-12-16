#include "Day7.h"

#include <algorithm>
#include <queue>
#include <ranges>
#include <set>

#include "../../utils/EmbeddedFile.h"
#include "../../utils/Memoization.h"

std::string aoc::day_7::part_1() noexcept
{
	auto lines = utils::embedded_file::embedded_input_by_line(utils::embedded_file::day_7_input_arr);

	/* TODO: since this same lambda is used twice, it would be nice to move it to a shared place like utils */
	const auto lambda_transform_to_vertical_lines = [&lines](const size_t& index)
		{
			return lines
				| std::views::transform([&index](const auto& s) { return s.at(index); })
				| std::ranges::to<std::string>();
		};

	const auto vertical_lines = std::views::iota(static_cast<size_t>(0), lines.front().size())
		| std::views::transform(lambda_transform_to_vertical_lines)
		| std::ranges::to<std::vector>();

	std::vector<std::pair<size_t, size_t>> beam_indexes;
	std::set<std::pair<size_t, size_t>> beam_indexes_set;

	for (size_t i = 0; i < vertical_lines.size(); ++i)
	{
		if (vertical_lines.at(i).front() == S_CHAR)
		{
			beam_indexes.emplace_back(i, 0);
			beam_indexes_set.insert(std::make_pair(i, 0));
			break;
		}
	}

	std::set < std::pair<size_t, size_t>> splitters;

	while (!beam_indexes.empty())
	{
		std::ranges::sort(beam_indexes);

		const auto beam_index = beam_indexes.front();

		for (size_t i = beam_index.second; i < vertical_lines.at(beam_index.first).size(); ++i)
		{
			if (vertical_lines.at(beam_index.first).at(i) == SPLITTER_CHAR)
			{
				std::vector new_beam_indexes =
				{
					std::make_pair(beam_index.first - 1, i),
					std::make_pair(beam_index.first + 1, i)
				};

				std::erase_if(new_beam_indexes, [&vertical_lines](const std::pair<size_t, size_t>& index) {return index.first < 0 || index.first >= vertical_lines.size(); });

				for (const auto& new_beam_index: new_beam_indexes)
				{
					if (!beam_indexes_set.contains(new_beam_index))
					{
						beam_indexes.push_back(new_beam_index);
						beam_indexes_set.insert(new_beam_index);
					}
				}

				splitters.insert(std::make_pair(beam_index.first, i));
				break;
			}

		}

		beam_indexes.erase(beam_indexes.begin());

	}


	return std::to_string(splitters.size());
}

std::string aoc::day_7::part_2() noexcept
{
	long long total = 0;

	auto lines = utils::embedded_file::embedded_input_by_line(utils::embedded_file::day_7_input_arr);

	/* TODO: since this same lambda is used twice, it would be nice to move it to a shared place like utils */
	const auto lambda_transform_to_vertical_lines = [&lines](const size_t& index)
		{
			return lines
				| std::views::transform([&index](const auto& s) { return s.at(index); })
				| std::ranges::to<std::string>();
		};

	const auto vertical_lines = std::views::iota(static_cast<size_t>(0), lines.front().size())
		| std::views::transform(lambda_transform_to_vertical_lines)
		| std::ranges::to<std::vector>();

	const auto counter = TimelinePathCounter(vertical_lines);

	auto memo_timeline_counter = utils::memoization::make_memoized_recursive(counter);

	for (size_t i = 0; i < vertical_lines.size(); ++i)
	{
		if (vertical_lines.at(i).front() == S_CHAR)
		{
			total = memo_timeline_counter(i, 0);
			break;
		}
	}

	return std::to_string(total);
}