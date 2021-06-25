#pragma once

#include <nyan/nyan.h>
#include "doctest.h"

// Define string monoid
NYAN_DECLARE_MONOID(std::string,
    "",
    [=](const auto x, const auto y) {
        return x + y;
    }
)

TEST_CASE("monoid")
{
    const std::string a = "hello";
    const std::string b = " ";
    const std::string c = "world";

    // Correct?
    constexpr auto o = nyan::Monoid<std::string>::operate;
    CHECK(o(a, o(b, c)) == "hello world");

    // Associative?
    CHECK(o(o(a, b), c) == o(a, o(b, c)));
    
    // Identity?
    const auto e = nyan::Monoid<std::string>::identity;
    CHECK(o(a, e) == a);
    CHECK(o(e, a) == a);
}
