#pragma once

#include <nyan/nyan.h>
#include "doctest.h"

TEST_CASE("compose")
{
    constexpr auto increment = [](const auto x){ return x + 1; };
    constexpr auto inc_and_double = nyan::compose(
        [](const auto x){ return x * 2; },
        increment
    );

    CHECK(inc_and_double(2) == 6);

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
