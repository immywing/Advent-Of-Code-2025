#ifndef DAY3_H
#define DAY3_H
#include <string>

namespace aoc::day_3
{
	constexpr int  TWELVE    = 12;
	constexpr char ZERO_CHAR = '0';

	struct Battery
	{
		int value;
		int index;
		Battery(const int& value, const int& index);
	};

	Battery pair_to_battery(const std::pair<int, char>& pair);

	std::string part_1() noexcept;
	std::string part_2() noexcept;
}
#endif