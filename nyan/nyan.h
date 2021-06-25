#pragma once

#include <functional>

namespace nyan
{
    template<class OuterFunc, class InnerFunc>
    constexpr decltype(auto) compose(OuterFunc outer, InnerFunc inner)
    {
        return [=](const auto x) { return outer(inner(x)); };
    }
}
