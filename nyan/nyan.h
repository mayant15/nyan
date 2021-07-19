/*!
 * nyan - functional programming utilities for C++
 *
 * Copyright (c) 2021 Mayant Mukul
 * Distributed under the MIT License. See the LICENSE file at
 * https://github.com/mayant15/nyan/blob/main/LICENSE
 * 
 */

#pragma once

#include "functors.h"

#define NYAN_DECLARE_MONOID(TYPE, IDENTITY, OPERATOR) \
    template <>                                       \
    struct nyan::Monoid<TYPE>                         \
    {                                                 \
        const static inline TYPE identity = IDENTITY; \
        static TYPE operate(TYPE x, TYPE y)           \
        {                                             \
            constexpr auto func = OPERATOR;           \
            return std::invoke(func, x, y);           \
        }                                             \
    };

namespace nyan::detail
{
    template <class... Types>
    struct is_singleton_pack : std::false_type
    {
    };

    template <class Type>
    struct is_singleton_pack<Type> : std::true_type
    {
    };

    // NOTE: Explicitly defined pair, tuple and array to be tuple-like
    //   should have some check of whether std::get exists
    template <class QueryType>
    struct is_tuple_like : std::false_type
    {
    };

    template <class... ContentTypes>
    struct is_tuple_like<std::tuple<ContentTypes...>> : std::true_type
    {
    };

    template <class... ContentTypes>
    struct is_tuple_like<std::pair<ContentTypes...>> : std::true_type
    {
    };

    template <class ContentType, size_t Size>
    struct is_tuple_like<std::array<ContentType, Size>> : std::true_type
    {
    };

    template <class Function, class... Args>
    inline decltype(auto) checked_apply(Function func, Args... args)
    {
        if constexpr (is_singleton_pack<Args...>::value)
        {
            if constexpr (is_tuple_like<Args...>::value)
            {
                // to check is_tuple_like we first need to ensure Args... is a singleton
                return std::apply(func, args...);
            }
            else
            {
                return std::apply(func, std::make_tuple(args...));
            }
        }
        else
        {
            return std::apply(func, std::make_tuple(args...));
        }
    }
}

namespace nyan
{
    template <class OuterFunc>
    inline constexpr decltype(auto) compose(OuterFunc outer)
    {
        return [=](const auto... args)
        {
            return detail::checked_apply(outer, args...);
        };
    }

    template <class OuterFunc, class... InnerFuncs>
    inline constexpr decltype(auto) compose(OuterFunc outer, InnerFuncs... inners)
    {
        return [=](const auto... args)
        {
            return detail::checked_apply(outer, std::invoke(compose(inners...), args...));
        };
    }

    template <class Type>
    struct Monoid
    {
        const static inline Type identity = Type{};
        static Type operate(Type x, Type y)
        {
            return Type{};
        }
    };
}
