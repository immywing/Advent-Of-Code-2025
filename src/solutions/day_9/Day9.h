#ifndef DAY9_H
#define DAY9_H

#include <string>

namespace aoc::day_9
{
	constexpr char COMMA_CHAR = ',';

	struct Vec2
	{
		long long x;
		long long y;

		bool operator==(const Vec2& other) const { return x == other.x && y == other.y; }
	};

	using pair_pair_ll = std::pair<Vec2, Vec2>;
	bool line_intersects_bounds_box(const Vec2& a, const Vec2& b, const pair_pair_ll& line) noexcept;

	std::string part_1() noexcept;
	std::string part_2() noexcept;
}
#endif
