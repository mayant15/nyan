#pragma once

#include <nyan/nyan.h>
#include "doctest.h"
#include <utility>

TEST_CASE("compose")
{
    SUBCASE("integer")
    {
        constexpr auto increment = [](const auto x){ return x + 1; };
        constexpr auto inc_and_double = nyan::compose(
            [](const auto x){ return x * 2; },
            increment
        );

        CHECK(inc_and_double(2) == 6);
    }

    SUBCASE("vector")
    {
        constexpr auto push = [](auto vec) { vec.push_back(10); return vec; };
        constexpr auto double_push = nyan::compose(
            push,
            push
        );

        std::vector<int> vec = { 2 };
        vec = double_push(vec);
        CHECK(vec.size() == 3);
        CHECK(vec[0] == 2);
        CHECK(vec[1] == 10);
        CHECK(vec[2] == 10);

        constexpr auto sum = [](const auto vec) {
            decltype(vec)::value_type s {};
            for (const auto& x : vec) {
                s += x;
            }
            return s;
        };
        constexpr auto push_and_sum = nyan::compose(sum, push);

        auto val = push_and_sum(vec);
        CHECK(val == 32);
        // push_and_sum should not have any side-effects, check
        CHECK(vec.size() == 3);
        CHECK(vec[0] == 2);
        CHECK(vec[1] == 10);
        CHECK(vec[2] == 10);
    }

    SUBCASE("more_than_two_functions")
    {
        constexpr auto a = [](const auto x) { return x + 3; };
        constexpr auto b = [](const auto y) { return y * 2; };
        constexpr auto c = [](const auto z) { return z + 2; };

        constexpr auto transform = nyan::compose(a, b, c);
        CHECK(transform(2) == 11);
    }

    SUBCASE("more_than_two_arguments")
    {
        constexpr auto a = [](const auto x, const auto y) { return std::pair { x + y, 2}; };
        constexpr auto b = [](const auto x, const auto y) { return std::tuple {x * y, 2, 3}; };
        constexpr auto c = [](const auto x, const auto y, const auto z) { return x - y + z; };

        CHECK(nyan::compose(a)(2, 3).first == 5);
        CHECK(std::get<0>(nyan::compose(b, a)(2, 3)) == 10);
        CHECK(nyan::compose(c, b, a)(2, 3) == 11);
    }

    SUBCASE("detail::is_tuple_like")
    {
        CHECK(nyan::detail::is_tuple_like<std::tuple<int, bool, double>>::value);
        CHECK(nyan::detail::is_tuple_like<std::pair<int, bool>>::value);
        CHECK(nyan::detail::is_tuple_like<std::array<double, 8>>::value);

        struct hello {};
        CHECK_FALSE(nyan::detail::is_tuple_like<hello>::value);
        CHECK_FALSE(nyan::detail::is_tuple_like<int>::value);
    }
}
