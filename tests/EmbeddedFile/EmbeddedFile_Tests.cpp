#include <gtest/gtest.h>

#include <array>
#include "utils/EmbeddedFile.h"


TEST(EmbeddedFile_Test, embedded_Input_by_line_produces_valid_vector)
{

	struct TestCase
	{
		const char* input;
		std::vector<std::string> expected;
	};

	std::array test_cases = 
	{
		TestCase
		{ 
			.input="ab\ncd\nef\n", 
			.expected{"ab", "cd", "ef"}
		},
		TestCase
		{
			.input = "ab\n\rcd\n\ref\n\r",
			.expected{"ab", "cd", "ef"}
		},
		TestCase
		{
			.input = "\n\n\n\n",
			.expected{"", "", "", ""}
		},
		TestCase
		{
			.input = "Single line",
			.expected{"Single line"}
		},
		TestCase
		{
			.input = "\nFirst line is empty",
			.expected{"", "First line is empty"}
		},
		TestCase
		{
			.input = "  \n\t\t\n",
			.expected{"  ", "\t\t"}
		},
		TestCase
		{
			.input = "",
			.expected{}
		},
	};

	for (const auto& test_case: test_cases)
	{
		auto actual = utils::embedded_file::embedded_input_by_line(test_case.input);
		EXPECT_EQ(actual, test_case.expected);
	}

}

