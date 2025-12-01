#include "Day1.h"

#include <iostream>

#include "../../utils/EmbeddedFile.h"

std::string aoc::day_1::part_1()
{
	int total = 0;
	uint8_t dial_position = DIAL_START_POSITION;
	for (const std::string& line: utils::embedded_file::embedded_input_by_line(utils::embedded_file::day_1_input_arr))
	{
		const int offset = std::stoi(line.substr(1));
		const int increment = line[0] == LEFT_CHAR ? DIAL_MODULUS - (offset % DIAL_MODULUS) : offset;
		dial_position = (dial_position + increment) % DIAL_MODULUS;
		total += dial_position == 0 ? 1 : 0;
	}

	return std::to_string(total);
}

std::string aoc::day_1::part_2()
{
	int total = 0;
	int dial_position = DIAL_START_POSITION;

	for (const std::string& line : utils::embedded_file::embedded_input_by_line(utils::embedded_file::day_1_input_arr))
	{
		const int offset = std::stoi(line.substr(1));

		const int increment = line[0] == LEFT_CHAR ? -1 : 1;

		for (int i = 0; i < offset; ++i)
		{
			dial_position += increment;
			dial_position %= DIAL_MODULUS;
			total += dial_position == 0 ? 1 : 0;
		}

	}

	return std::to_string(total);
}
