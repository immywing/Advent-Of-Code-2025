#ifndef UTILS_EMBEDDED_FILE_H
#define UTILS_EMBEDDED_FILE_H

#include <expected>
#include <string>
#include <vector>

namespace utils::embedded_file
{
	#define MAKE_LITERAL(X) #X
	#define EMBED_PATH(X) MAKE_LITERAL(X)

	#define INPUTS_DIR  ../../inputs

	#define DAY_1_FILE  day_1.txt
	#define DAY_2_FILE  day_2.txt
	#define DAY_3_FILE  day_3.txt
	#define DAY_4_FILE  day_4.txt
	#define DAY_5_FILE  day_5.txt
	#define DAY_6_FILE  day_6.txt
	#define DAY_7_FILE  day_7.txt
	#define DAY_8_FILE  day_8.txt
	#define DAY_9_FILE  day_9.txt
	#define DAY_10_FILE day_10.txt
	#define DAY_11_FILE day_11.txt
	#define DAY_12_FILE day_12.txt

	#define DAY_1_PATH  EMBED_PATH(INPUTS_DIR/DAY_1_FILE)
	#define DAY_2_PATH  EMBED_PATH(INPUTS_DIR/DAY_2_FILE)
	#define DAY_3_PATH  EMBED_PATH(INPUTS_DIR/DAY_3_FILE)
	#define DAY_4_PATH  EMBED_PATH(INPUTS_DIR/DAY_4_FILE)
	#define DAY_5_PATH  EMBED_PATH(INPUTS_DIR/DAY_5_FILE)
	#define DAY_6_PATH  EMBED_PATH(INPUTS_DIR/DAY_6_FILE)
	#define DAY_7_PATH  EMBED_PATH(INPUTS_DIR/DAY_7_FILE)
	#define DAY_8_PATH  EMBED_PATH(INPUTS_DIR/DAY_8_FILE)
	#define DAY_9_PATH  EMBED_PATH(INPUTS_DIR/DAY_9_FILE)
	#define DAY_10_PATH EMBED_PATH(INPUTS_DIR/DAY_10_FILE)
	#define DAY_11_PATH EMBED_PATH(INPUTS_DIR/DAY_11_FILE)
	#define DAY_12_PATH EMBED_PATH(INPUTS_DIR/DAY_12_FILE)

	constexpr char NULL_TERMINATOR = '\0';
	constexpr char NEW_LINE_ESCAPE = '\n';
	constexpr char RETURN_CARRIAGE = '\r';

	const char day_1_input_arr[] =
	{
		#embed DAY_1_PATH if_empty('M', 'i', 's', 's', 'i', 'n', 'g', '\n')
		,NULL_TERMINATOR
	};

	const char day_2_input_arr[] =
	{
		#embed DAY_2_PATH if_empty('M', 'i', 's', 's', 'i', 'n', 'g', '\n')
		,NULL_TERMINATOR
	};

	const char day_3_input_arr[] =
	{
		#embed DAY_3_PATH if_empty('M', 'i', 's', 's', 'i', 'n', 'g', '\n')
		,NULL_TERMINATOR
	};

	const char day_4_input_arr[] =
	{
		#embed DAY_4_PATH if_empty('M', 'i', 's', 's', 'i', 'n', 'g', '\n')
		,NULL_TERMINATOR
	};

	const char day_5_input_arr[] =
	{
		#embed DAY_5_PATH if_empty('M', 'i', 's', 's', 'i', 'n', 'g', '\n')
		,NULL_TERMINATOR
	};

	const char day_6_input_arr[] =
	{
		#embed DAY_6_PATH if_empty('M', 'i', 's', 's', 'i', 'n', 'g', '\n')
		,NULL_TERMINATOR
	};

	const char day_7_input_arr[] =
	{
		#embed DAY_7_PATH if_empty('M', 'i', 's', 's', 'i', 'n', 'g', '\n')
		,NULL_TERMINATOR
	};

	const char day_8_input_arr[] =
	{
		#embed DAY_8_PATH if_empty('M', 'i', 's', 's', 'i', 'n', 'g', '\n')
		,NULL_TERMINATOR
	};

	const char day_9_input_arr[] =
	{
		#embed DAY_9_PATH if_empty('M', 'i', 's', 's', 'i', 'n', 'g', '\n')
		,NULL_TERMINATOR
	};

	const char day_10_input_arr[] =
	{
		#embed DAY_10_PATH if_empty('M', 'i', 's', 's', 'i', 'n', 'g', '\n')
		,NULL_TERMINATOR
	};

	const char day_11_input_arr[] =
	{
		#embed DAY_11_PATH if_empty('M', 'i', 's', 's', 'i', 'n', 'g', '\n')
		,NULL_TERMINATOR
	};

	const char day_12_input_arr[] =
	{
		#embed DAY_12_PATH if_empty('M', 'i', 's', 's', 'i', 'n', 'g', '\n')
		,NULL_TERMINATOR
	};


	std::vector<std::string> embedded_input_by_line(const char* embedded_input, const char& separator = NEW_LINE_ESCAPE) noexcept;

}
#endif