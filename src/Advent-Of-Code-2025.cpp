// Advent-Of-Code-2025.cpp : Defines the entry point for the application.

#include "Advent-Of-Code-2025.h"

#include "solutions/day_1/Day1.h"
#include "utils/EmbeddedFile.h"

int main()
{
	/* TODO */
	/* Not yet decided on how the main app should run. possibly args to request solutions for a specific day, or threads to solve each puzzle concurrently */
	std::cout << aoc::day_1::part_1() << '\n';
	std::cout << aoc::day_1::part_2() << '\n';
    return 0;
}
