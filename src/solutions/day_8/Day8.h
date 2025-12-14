#ifndef DAY8_H
#define DAY8_H

#include <string>
#include <vector>

#include "../../utils/Memoization.h"

namespace aoc::day_8
{
	constexpr char COMMA_CHAR = ',';

	constexpr size_t N_CIRCUITS = 1000;

	struct Vec3
	{
		long long x;
		long long y;
		long long z;

		Vec3(const long long& x, const long long& y, const long long& z);

		//Vec3(const std::vector<long long>& vector);
		Vec3() = default;

		bool operator==(const Vec3& other) const;
        bool operator< (const Vec3& other) const;
	};

    struct Vec3Hash
    {
        size_t operator()(const Vec3& v) const {
            std::size_t seed = 0;

            utils::memoization::hash_combine(seed, v.x);
            utils::memoization::hash_combine(seed, v.y);
            utils::memoization::hash_combine(seed, v.z);

            return seed;
        }
    };

    struct PairVec3Hash {
        size_t operator()(const std::pair<Vec3, Vec3>& state) const {
            // Hash the components

            size_t h1 = Vec3Hash()(state.first);
            size_t h2 = Vec3Hash()(state.second);

            // Combine the hashes (a robust method)
            return h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
        }
    };

    struct TupleVec3Hash {
        size_t operator()(const std::tuple<Vec3, Vec3>& key_tuple) const {
            // ... Logic to extract the two Vec3s and combine their hashes ...
            // Using std::apply is the cleanest way here:
            size_t seed = 0;
            std::apply([&](const Vec3& v1, const Vec3& v2) {
                // Assuming Vec3Hash is defined to hash a single Vec3
                utils::memoization::hash_combine(seed, Vec3Hash()(v1));
                utils::memoization::hash_combine(seed, Vec3Hash()(v2));
                }, key_tuple);
            return seed;
        }
    };

	long long calculate_distance(const Vec3& a, const Vec3& b);

	std::string part_1() noexcept;
	std::string part_2() noexcept;
}
#endif

