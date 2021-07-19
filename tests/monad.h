#pragma once

#include <nyan/nyan.h>
#include "doctest.h"

TEST_CASE("indentity_monad")
{
    CHECK(1 == 1);
    // constexpr auto transformer = [](const int data) {
    //     return nyan::functor::Id(data)
    //         .map([](const auto x) { return x + 3; })
    //         .map([](const auto y) { return y * 2; })
    //         .fold([](const auto z) { return z + 2; });
    // };

    // CHECK(transformer(3) == 14);
}
