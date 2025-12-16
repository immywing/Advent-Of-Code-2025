#include "EmbeddedFile.h"

std::vector<std::string> utils::embedded_file::embedded_input_by_line(const char* embedded_input, const char& separator) noexcept
{
	std::vector<std::string> lines;
	size_t start = 0;
	size_t end = 0;
	for (; embedded_input[end] != NULL_TERMINATOR; ++end)
	{
		if (embedded_input[end] == separator)
		{
			size_t length = (end - start > 0) && embedded_input[end - 1] == RETURN_CARRIAGE ? end - start - 1: end - start;

			lines.emplace_back(embedded_input + start, length);
			start = end + 1;
		}
	}

	if (embedded_input[start] != NULL_TERMINATOR)
	{
		size_t length = (end - start > 0) && embedded_input[end - 1] == RETURN_CARRIAGE ? end - start - 1 : end - start;
		lines.emplace_back(embedded_input + start, length);
	}

	return lines;
}
