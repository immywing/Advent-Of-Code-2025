#ifndef DAY11_H
#define DAY11_H

#include <algorithm>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../utils/Memoization.h"

namespace aoc::day_11
{
	constexpr char COLON_CHAR = ':';
	constexpr char SPACE_CHAR = ' ';

	const std::string YOU = "you";
	const std::string OUT = "out";
	const std::string SVR = "svr";
	const std::string DAC = "dac";
	const std::string FFT = "fft";

	struct PathLog
	{
		std::string current_device;
		bool dac;
		bool fft;

		explicit PathLog(std::string device);
		PathLog(std::string device, bool dac, bool fft);
	};

	class DevicePathCounter
	{
	public:
		explicit DevicePathCounter(const std::unordered_map<std::string, std::vector<PathLog>>& device_map) : device_map_(device_map) {}

		template<typename Self>
		long long operator()(Self& self, const std::string& current_device, const bool& dac, const bool& fft) const noexcept
		{
			return count_paths(self, current_device, dac, fft);
		}

	private:
		std::unordered_map<std::string, std::vector<PathLog>> device_map_;

		template <typename Self>
		long long count_paths(Self& self, const std::string& current_device, const bool& dac, const bool& fft) const noexcept
		{
			if (current_device == OUT && dac && fft) { return 1LL; }

			if (current_device == OUT) { return 0LL; }

			auto recursive_results = device_map_.at(current_device) 
				| std::views::transform([&](const PathLog& pl) { return self(pl.current_device, dac ? dac : pl.dac, fft ? fft : pl.fft); });

			return  std::ranges::fold_left(recursive_results, 0LL, std::plus<long long>());
		}
	};

	std::pair<std::string, std::vector<PathLog>> transform_line(const std::string& line);

	std::string part_1() noexcept;
	std::string part_2() noexcept;
}
#endif
