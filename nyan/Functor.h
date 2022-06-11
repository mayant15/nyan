/*!
 * @file Functor.h
 * @brief Functor concept enforcing an fmap implementation
 * @note Technically this is an endofunctor on the category of types, not any general functor
 *
 * Functor from category C to category D is a function which takes objects
 * in C to objects in D
 * a |-> F a
 *
 * And it takes morphisms in C to morphisms in D, preserving composition
 * if f :: a -> b
 * then F f :: F a -> F b
 *
 * This is implemented via a higher-order function fmap
 * fmap :: (a -> b) -> (F a -> F b)
 */

#pragma once

#include <concepts>
#include <type_traits>

#include "support.h"

namespace nyan
{
    template <template <class> class F, class a, class b>
    struct fmap
    {
        static constexpr bool implemented = false;
        Function<F<a>, F<b>> operator()(const Function<a, b> &) const;
    };

    template <template <class> class F, class a, class b>
    concept Functor = fmap<F, a, b>::implemented && requires
    {
        typename F<a>;
        typename F<b>;
    };

    template <template <class> class F, class a, class b>
    requires Functor<F, a, b>
    auto map(const Function<a, b> &f, const F<a> &obj) -> F<b>
    {
        return fmap<F, a, b>{}(f)(obj);
    }
}
