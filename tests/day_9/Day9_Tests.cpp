#include <gtest/gtest.h>
#include <array>

#include "solutions/day_9/Day9.h"

TEST(Day_8_Tests, line_intersects_bounds_box)
{

	struct TestCase
	{
		aoc::day_9::Vec2 a;
		aoc::day_9::Vec2 b;
		aoc::day_9::pair_pair_ll line;
		bool expected;
	};

	constexpr std::array test_cases = 
	{
		TestCase
		{
			.a = aoc::day_9::Vec2{.x = 5, .y = 5}, 
			.b = aoc::day_9::Vec2{.x = 10, .y = 10}, 
			.line = std::make_pair(aoc::day_9::Vec2{.x = 3, .y = 6}, aoc::day_9::Vec2{.x = 7, .y = 6}) , 
			.expected = true
		},
		TestCase
		{
			.a = aoc::day_9::Vec2{.x = 5, .y = 5},
			.b = aoc::day_9::Vec2{.x = 10, .y = 10},
			.line = std::make_pair(aoc::day_9::Vec2{.x = 5, .y = 6}, aoc::day_9::Vec2{.x = 7, .y = 6}) ,
			.expected = true
		},
		TestCase
		{
			.a = aoc::day_9::Vec2{.x = 5, .y = 5},
			.b = aoc::day_9::Vec2{.x = 10, .y = 10},
			.line = std::make_pair(aoc::day_9::Vec2{.x = 3, .y = 6}, aoc::day_9::Vec2{.x = 11, .y = 6}) ,
			.expected = true
		},
		TestCase
		{
			.a = aoc::day_9::Vec2{.x = 5, .y = 5},
			.b = aoc::day_9::Vec2{.x = 10, .y = 10},
			.line = std::make_pair(aoc::day_9::Vec2{.x = 6, .y = 6}, aoc::day_9::Vec2{.x = 11, .y = 6}) ,
			.expected = true
		},
		TestCase
		{
			.a = aoc::day_9::Vec2{.x = 5, .y = 5},
			.b = aoc::day_9::Vec2{.x = 10, .y = 10},
			.line = std::make_pair(aoc::day_9::Vec2{.x = 6, .y = 6}, aoc::day_9::Vec2{.x = 10, .y = 6}) ,
			.expected = true
		},
		TestCase
		{
			.a = aoc::day_9::Vec2{.x = 5, .y = 5},
			.b = aoc::day_9::Vec2{.x = 10, .y = 10},
			.line = std::make_pair(aoc::day_9::Vec2{.x = 3, .y = 6}, aoc::day_9::Vec2{.x = 10, .y = 6}) ,
			.expected = true
		},
		TestCase
		{
			.a = aoc::day_9::Vec2{.x = 5, .y = 5},
			.b = aoc::day_9::Vec2{.x = 10, .y = 10},
			.line = std::make_pair(aoc::day_9::Vec2{.x = 6, .y = 3}, aoc::day_9::Vec2{.x = 6, .y = 7}) ,
			.expected = true
		},
		TestCase
		{
			.a = aoc::day_9::Vec2{.x = 5, .y = 5},
			.b = aoc::day_9::Vec2{.x = 10, .y = 10},
			.line = std::make_pair(aoc::day_9::Vec2{.x = 6, .y = 5}, aoc::day_9::Vec2{.x = 6, .y = 7}) ,
			.expected = true
		},
		TestCase
		{
			.a = aoc::day_9::Vec2{.x = 5, .y = 5},
			.b = aoc::day_9::Vec2{.x = 10, .y = 10},
			.line = std::make_pair(aoc::day_9::Vec2{.x = 6, .y = 3}, aoc::day_9::Vec2{.x = 6, .y = 11}) ,
			.expected = true
		},
		TestCase
		{
			.a = aoc::day_9::Vec2{.x = 5, .y = 5},
			.b = aoc::day_9::Vec2{.x = 10, .y = 10},
			.line = std::make_pair(aoc::day_9::Vec2{.x = 6, .y = 6}, aoc::day_9::Vec2{.x = 6, .y = 11}) ,
			.expected = true
		},
		TestCase
		{
			.a = aoc::day_9::Vec2{.x = 5, .y = 5},
			.b = aoc::day_9::Vec2{.x = 10, .y = 10},
			.line = std::make_pair(aoc::day_9::Vec2{.x = 6, .y = 6}, aoc::day_9::Vec2{.x = 6, .y = 10}) ,
			.expected = true
		},
		TestCase
		{
			.a = aoc::day_9::Vec2{.x = 5, .y = 5},
			.b = aoc::day_9::Vec2{.x = 10, .y = 10},
			.line = std::make_pair(aoc::day_9::Vec2{.x = 6, .y = 3}, aoc::day_9::Vec2{.x = 6, .y = 10}) ,
			.expected = true
		},

		TestCase
		{
			.a = aoc::day_9::Vec2{.x = 5, .y = 5},
			.b = aoc::day_9::Vec2{.x = 10, .y = 10},
			.line = std::make_pair(aoc::day_9::Vec2{.x = 6, .y = 0}, aoc::day_9::Vec2{.x = 6, .y = 5}) ,
			.expected = false
		},
		TestCase
		{
			.a = aoc::day_9::Vec2{.x = 5, .y = 5},
			.b = aoc::day_9::Vec2{.x = 10, .y = 10},
			.line = std::make_pair(aoc::day_9::Vec2{.x = 6, .y = 10}, aoc::day_9::Vec2{.x = 6, .y = 15}) ,
			.expected = false
		},
		TestCase
		{
			.a = aoc::day_9::Vec2{.x = 5, .y = 5},
			.b = aoc::day_9::Vec2{.x = 10, .y = 10},
			.line = std::make_pair(aoc::day_9::Vec2{.x = 0, .y = 6}, aoc::day_9::Vec2{.x = 5, .y = 6}) ,
			.expected = false
		},
		TestCase
		{
			.a = aoc::day_9::Vec2{.x = 5, .y = 5},
			.b = aoc::day_9::Vec2{.x = 10, .y = 10},
			.line = std::make_pair(aoc::day_9::Vec2{.x = 10, .y = 10}, aoc::day_9::Vec2{.x = 15, .y = 15}) ,
			.expected = false
		},
		TestCase
		{
			.a = aoc::day_9::Vec2{.x = 9, .y = 3},
			.b = aoc::day_9::Vec2{.x = 2, .y = 5},
			.line = std::make_pair(aoc::day_9::Vec2{.x = 7, .y = 3}, aoc::day_9::Vec2{.x = 7, .y = 1}) ,
			.expected = false
		},
	};
	
	for (const auto& test_case: test_cases)
	{
		EXPECT_EQ(test_case.expected, aoc::day_9::line_intersects_bounds_box(test_case.a, test_case.b, test_case.line));
	}

}