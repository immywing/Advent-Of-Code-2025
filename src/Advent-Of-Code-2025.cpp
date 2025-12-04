// Advent-Of-Code-2025.cpp : Defines the entry point for the application.

#include "Advent-Of-Code-2025.h"

#include "solutions/day_1/Day1.h"
#include "solutions/day_2/Day2.h"
#include "solutions/day_3/Day3.h"
#include "solutions/day_4/Day4.h"
#include "utils/EmbeddedFile.h"

int main()
{
	/* TODO Not yet decided on how the main app should run. possibly args to request solutions for a specific day, or threads to solve each puzzle concurrently */
	std::cout << "day 1 - part 1: " << aoc::day_1::part_1() << '\n';
	std::cout << "day 1 - part 2: " << aoc::day_1::part_2() << '\n';
	std::cout << "day 2 - part 1: " << aoc::day_2::part_1() << '\n';
	std::cout << "day 2 - part 2: " << aoc::day_2::part_2() << '\n';
	std::cout << "day 3 - part 1: " << aoc::day_3::part_1() << '\n';
	std::cout << "day 3 - part 2: " << aoc::day_3::part_2() << '\n';
	std::cout << "day 4 - part 1: " << aoc::day_4::part_1() << '\n';
	std::cout << "day 4 - part 2: " << aoc::day_4::part_2() << '\n';
    return 0;
}
