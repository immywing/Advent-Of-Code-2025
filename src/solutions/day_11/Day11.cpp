#include "Day11.h"

#include <queue>

#include "../../utils/EmbeddedFile.h"


aoc::day_11::PathLog::PathLog(std::string device) : current_device(std::move(device)), dac(current_device == DAC), fft(current_device == FFT)
{
}

aoc::day_11::PathLog::PathLog(std::string device, const bool dac, const bool fft) : current_device(std::move(device)), dac(dac), fft(fft)
{
}

std::pair<std::string, std::vector<aoc::day_11::PathLog>> aoc::day_11::transform_line(const std::string& line)
{
	auto vec = line
		| std::views::split(COLON_CHAR)
		| std::views::transform([](auto&& subrange) { return std::string(subrange.begin(), subrange.end()); })
		| std::ranges::to<std::vector<std::string>>();

	auto key = vec.front();

	auto value = vec.back()
		| std::views::split(SPACE_CHAR)
		| std::views::transform([](auto&& subrange) { return std::string(subrange.begin(), subrange.end()); })
		| std::views::filter([](const std::string& s) { return !s.empty(); })
		| std::views::transform([](const std::string& str) { return PathLog{ str }; })
		| std::ranges::to<std::vector>();

	return std::make_pair(key, value);
}

std::string aoc::day_11::part_1() noexcept
{
	auto device_map = utils::embedded_file::embedded_input_by_line(utils::embedded_file::day_11_input_arr)
		| std::views::transform(transform_line)
		| std::ranges::to<std::unordered_map>();

	std::queue<PathLog> queue;

	queue.push_range(device_map[YOU]);

	long long total = 0;

	while (!queue.empty())
	{
		auto device = queue.front();
		queue.pop();

		if (device.current_device == OUT)
		{
			total++;
			continue;
		}

		queue.push_range(device_map[device.current_device]);
	}

	return std::to_string(total);
}

std::string aoc::day_11::part_2() noexcept
{
	const auto device_map = utils::embedded_file::embedded_input_by_line(utils::embedded_file::day_11_input_arr)
		| std::views::transform(transform_line)
		| std::ranges::to<std::unordered_map>();

	const auto path_counter = DevicePathCounter(device_map);

	auto memo_path_counter = utils::memoization::make_memoized_recursive(path_counter);

	const auto total = memo_path_counter(SVR, false, false);
	return std::to_string(total);
}
