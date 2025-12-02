#ifndef DAY2_H
#define DAY2_H
#include <string>

namespace aoc::day_2
{
	constexpr char COMMA_CHAR  = ',';
	constexpr char HYPHEN_CHAR = '-';

	bool dup_check(const std::string& left, const std::string& right);

	std::string part_1();
	std::string part_2();
}
#endif