#include "Day8.h"

#include <algorithm>
#include <iostream>
#include <ranges>
#include <unordered_set>

#include "../../utils/EmbeddedFile.h"

aoc::day_8::Vec3::Vec3(const long long& x, const long long& y, const long long& z) : x(x), y(y), z(z) {}

//aoc::day_8::Vec3::Vec3(const std::vector<long long>& vector) : x(vector.at(0)), y(vector.at(1)), z(vector.at(2)) {}

bool aoc::day_8::Vec3::operator==(const Vec3& other) const
{
	return x == other.x && y == other.y && z == other.z;
}

bool aoc::day_8::Vec3::operator<(const Vec3& other) const
{
	return x < other.x && y < other.y && z < other.z;
}

long long aoc::day_8::calculate_distance(const Vec3& a, const Vec3& b)
{
	const auto dx = a.x - b.x;
	const auto dy = a.y - b.y;
	const auto dz = a.z - b.z;
	return (dx * dx) + (dy * dy) + (dz * dz);
}

std::string aoc::day_8::part_1() noexcept
{

	const auto lines = utils::embedded_file::embedded_input_by_line(utils::embedded_file::day_8_input_arr);

	const auto lambda_split_string_by_comma = [](const std::string& line)
		{
			return line
				| std::views::split(COMMA_CHAR)
				| std::views::transform([](auto&& subrange) { return std::string(subrange.begin(), subrange.end()); })
				| std::ranges::to<std::vector>();
		};

	const auto lambda_comma_delimited_to_vec3 = [](const std::vector<std::string>& vec)
		{
			const auto longs = vec
				| std::views::transform([](const std::string& str) { return std::stoll(str); })
				| std::ranges::to<std::vector>();

			return Vec3(longs.at(0), longs.at(1), longs.at(2));
		};

	auto comma_separated_lines = lines
		| std::views::transform(lambda_split_string_by_comma)
		| std::ranges::to<std::vector>();

	auto vec3_vector = comma_separated_lines
		| std::views::transform(lambda_comma_delimited_to_vec3)
		| std::ranges::to<std::vector>();

	std::unordered_set<std::pair<Vec3, Vec3>, PairVec3Hash> vec3_set;
	std::vector<std::unordered_set<Vec3, Vec3Hash>> circuits;

	auto memo_calculate_distance = utils::memoization::make_memoized(calculate_distance, TupleVec3Hash{});

	for (size_t i = 0; i < N_CIRCUITS; )
	{
		std::cout << i << '\n';
		long long min_distance = std::numeric_limits<long long>::max();
		std::pair<Vec3, Vec3> pair;

		for (const auto& vec_a: vec3_vector)
		{
			for (const auto& vec_b: vec3_vector)
			{
				auto curr_pair = std::make_pair(vec_a, vec_b); //vec_a < vec_b ? std::make_pair(vec_a, vec_b) : std::make_pair(vec_b, vec_a);

				if (const auto distance = memo_calculate_distance(vec_a, vec_b); vec_a != vec_b && distance < min_distance && !vec3_set.contains(curr_pair))
				{
					min_distance = distance;
					pair = curr_pair;
				}
			}
		}

		vec3_set.insert(pair);

		//if (std::ranges::any_of(circuits, [&pair](const auto& set) { return set.contains(pair.first) && set.contains(pair.second); })) { continue; }

		bool create_new_circuit = true;

		for (auto& set : circuits)
		{
			auto contains_first  = set.contains(pair.first);
			auto contains_second = set.contains(pair.second);

			if ((contains_first && !contains_second) || (!contains_first && contains_second))
			{
				set.insert(pair.first);
				set.insert(pair.second);
				create_new_circuit = false;
				break;
			}
		}

		if (create_new_circuit)
		{
			std::unordered_set<Vec3, Vec3Hash> new_circuit;
			new_circuit.insert(pair.first);
			new_circuit.insert(pair.second);
			circuits.push_back(new_circuit);
		}

		++i;
	}

	std::cout << "\n\n------------------\n";

	std::ranges::sort(circuits, [](const auto& a, const auto& b) {return a.size() > b.size(); });
	auto total = circuits[0].size() * circuits[1].size() * circuits[2].size();
	return std::to_string(total);
}

std::string aoc::day_8::part_2() noexcept
{
	return "";
}
