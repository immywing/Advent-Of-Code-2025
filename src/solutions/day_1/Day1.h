#ifndef DAY1_H
#define DAY1_H
#include <string>

namespace aoc::day_1
{
	constexpr int DIAL_START_POSITION = 50;
	constexpr int DIAL_MODULUS = 100;
	constexpr char LEFT_CHAR = 'L';

	std::string part_1() noexcept;
	std::string part_2() noexcept;
}
#endif