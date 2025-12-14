#ifndef DAY7_H
#define DAY7_H

#include <string>
#include <unordered_map>
#include <vector>

namespace aoc::day_7
{
	constexpr char S_CHAR = 'S';
    constexpr char SPLITTER_CHAR = '^';

	std::string part_1() noexcept;
	std::string part_2() noexcept;


    struct PairHash {
        size_t operator()(const std::pair<int, size_t>& state) const {
            std::hash<int> int_hasher;
            std::hash<size_t> size_t_hasher;

            // Hash the components
            size_t h1 = int_hasher(state.first);
            size_t h2 = size_t_hasher(state.second);

            // Combine the hashes (a robust method)
            return h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
        }
    };

    class TimelinePathCounter
    {
    public:
	    explicit TimelinePathCounter(const std::vector<std::string>& lines) : lines_(lines), lines_size_(static_cast<int>(lines.size())) {}

        template<typename Self>
        long long operator()(Self& self, const int& index, const size_t& start_pos) const noexcept
	    {
            return count_paths(self, index, start_pos);
	    }

    private:
        std::vector<std::string> lines_;
        int lines_size_;
        char splitter_char_ = '^';

        template <typename Self>
        long long count_paths(Self& self, const int& index, const size_t& start_pos) const noexcept
        {
            long long total = 0;

            const auto& splitter_pos = lines_.at(index).find(splitter_char_, start_pos);

            const bool end = splitter_pos == std::string::npos;

            if (index - 1 >= 0 && !end) { total += self(index - 1, splitter_pos); }

            if (index + 1 < lines_size_ && !end) { total += self(index + 1, splitter_pos); }

            if (end) { return 1; }

            return total;
        }
    };


}
#endif