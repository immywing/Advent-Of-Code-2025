#ifndef UTILS_MEMOIZATION_H
#define UTILS_MEMOIZATION_H
#include <functional>

namespace utils::memoization
{
    template <class T>
    inline void hash_combine(std::size_t& seed, const T& v)
    {
        seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    //template <typename...Ts>
    //struct std::hash<std::tuple<Ts...>>
    //{
    //    size_t operator() (const std::tuple<Ts...>& t) const
    //    {
    //        size_t seed = 0;
    //        std::apply([&](auto const&... xs) { (hash_combine(seed, xs), ...); }, t);
    //        return seed;
    //    }
    //};

    template <typename Func, typename Hasher = std::hash<std::tuple<>>>
    class Memoized
    {
    public:
        explicit Memoized(Func f) : func(std::move(f)) {}

        template <typename... Args>
        auto operator() (Args&&... args)
        {
            using tuple_key_t = std::tuple<std::decay_t<Args>...>;
            using return_t    = std::invoke_result_t<Func, Args...>;

            using final_hasher_t = std::conditional_t<
                std::is_same_v<Hasher, std::hash<std::tuple<>>>,
                std::hash<tuple_key_t>,
                Hasher
            >;

            static std::unordered_map<tuple_key_t, return_t, final_hasher_t> cache;

            tuple_key_t key = std::make_tuple(args...);

            if (auto it = cache.find(key); it != cache.end())
            {
                return it->second;
            }

            auto result = std::invoke(func, std::forward<Args>(args)...);
            cache.emplace(std::move(key), result);
            return result;
        }

    private:
        Func func;
    };

    template<class F>
    auto make_memoized(F f)
    {
        return Memoized<F>{std::move(f)};
    }

    template<class F, class H>
    auto make_memoized(F f, H)
    {
        // Explicitly pass the Hasher type H to the Memoized class.
        return Memoized<F, H>{std::move(f)};
    }

    template <typename Func, typename Hasher = std::hash<std::tuple<>>>
    class MemoizedRecursive
    {
    public:
        explicit MemoizedRecursive(Func f) : func(std::move(f)) {}

        template <typename... Args>
        auto operator() (Args&&... args)
        {
            using tuple_key_t = std::tuple<std::decay_t<Args>...>;
            using return_t = std::invoke_result_t<Func, MemoizedRecursive&, Args...>;

            using final_hasher_t = std::conditional_t<
                std::is_same_v<Hasher, std::hash<std::tuple<>>>,
                std::hash<tuple_key_t>,
                Hasher
            >;

            static std::unordered_map<tuple_key_t, return_t, final_hasher_t> cache;

            tuple_key_t key = std::make_tuple(args...);
			

            if (auto it = cache.find(key); it != cache.end())
            {
                return it->second;
            }

            auto& self = *this;
            auto result = std::invoke(func, self, std::forward<Args>(args)...);
            cache.emplace(std::move(key), result);
            return result;
        }

    private:
        Func func;
    };

    template<class F>
    auto make_memoized_recursive(F f) 
	{
        return MemoizedRecursive<F>{std::move(f)};
    }

    template<class F, class H>
    auto make_memoized_recursive(F f, H)
    {
        return MemoizedRecursive<F, H>{std::move(f)};
    }
}

namespace std
{
    template <typename...Ts>
    struct hash<std::tuple<Ts...>>
    {
        size_t operator() (const std::tuple<Ts...>& t) const
        {
            size_t seed = 0;
            std::apply([&](auto const&... xs) { (utils::memoization::hash_combine(seed, xs), ...); }, t);
            return seed;
        }
    };
}

#endif
