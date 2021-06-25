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
}
