/*!
 * nyan - functional programming utilities for C++
 *
 * Copyright (c) 2021 Mayant Mukul
 * Distributed under the MIT License. See the LICENSE file at
 * https://github.com/mayant15/nyan/blob/main/LICENSE
 * 
 */

#pragma once

#include <functional>

#define NYAN_DECLARE_MONOID(TYPE, IDENTITY, OPERATOR) \
template<> struct nyan::Monoid<TYPE> { \
    const static inline TYPE identity = IDENTITY; \
    static TYPE operate(TYPE x, TYPE y) { \
        constexpr auto func = OPERATOR; \
        return std::invoke(func, x, y); \
    } \
};

namespace nyan
{
    template<class OuterFunc>
    constexpr decltype(auto) compose(OuterFunc outer)
    {
        return [=](const auto x) { return outer(x); };
    }

    template<class OuterFunc, class... InnerFuncs>
    constexpr decltype(auto) compose(OuterFunc outer, InnerFuncs... inners)
    {
        return [=](const auto x) { 
            return outer(
                std::invoke(compose(inners...), x)
            ); 
        };
    }

    template<class Type>
    struct Monoid
    {
        const static inline Type identity = Type {};
        static Type operate(Type x, Type y) 
        {
            return Type {};
        }
    };

    template<class Type>
    struct Id
    {
        Id(Type data) : _data(data) {}

        template<class Function>
        Id map(Function func)
        {
            return Id(func(_data));
        }

        template<class Function>
        Type fold(Function func)
        {
            return func(_data);
        }

        Type unwrap() const
        {
            return _data;
        }

    private:
        Type _data;
    };
}
