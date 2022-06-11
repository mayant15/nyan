#pragma once

#include <functional>
#include <iostream>
#include <cstdlib>

#define NYAN_PANIC() std::abort()

#define NYAN_ENFORCE(EXPRESSION)                                        \
    {                                                                   \
        if (!(EXPRESSION))                                              \
        {                                                               \
            throw std::runtime_error("Assertion failed: " #EXPRESSION); \
        }                                                               \
    }

namespace nyan
{
    template <typename I, typename O>
    using Function = std::function<O(I)>;
}
