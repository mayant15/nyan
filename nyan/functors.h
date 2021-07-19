#pragma once

#include "base.h"

namespace nyan::mixins
{
    // TODO: Have a functor concept, also to specialize a global utility map for functors
    struct Functor
    {
        //
    };
}

namespace nyan::functors
{

    /**
     * Note: Mathematically, a functor should be something like this,
     *   but it would be nice to have a few helper functions on this
     *   class, and also have a type to distinguish these. Which is
     *   why we usually create a class, where the constructor is the
     *   object mapping, and map() is the morphism mapping, which also
     *   applies the new morphism
     * 
        struct Functor
        {
            template <class TData>
            static TData object(TData arg)
            {
                return arg_mapped_to_an_object;
            }

            template <class TFunction>
            static TFunction morphism(TFunction function)
            {
                return function_mapped_to_a_morphism;
            }
        };
    */

    template <class TData>
    struct Id
    {
        Id(TData data) : _data(data) {}

        template <class TFunction>
        auto map(TFunction function) const
        {
            return Id(function(_data));
        }

        std::string print() const
        {
            return "Identity (" + _data + ")";
        }

    private:
        const TData _data;
    };

    template <class TData>
    struct Optional;

    template <class TData>
    struct Some
    {
        Some(TData data) : _data(data) {}

    private:
        TData _data;
        friend struct Optional<TData>;
    };

    struct None
    {
    };

    template <class TData>
    struct Optional
    {
        Optional() : _none(), _is_empty(true) {}

        Optional(TData data) : _some(data), _is_empty(false) {}

        template <class TFunction>
        auto map(TFunction function) const {
            return _is_empty ? Optional() : Optional(function(_some._data))}

        std::string print() const
        {
            return _is_empty ? "None" : "Some(" + _some._data + ")";
        }

        TData unsafe_unwrap() const
        {
            return _some._data;
        }

    private:
        const bool _is_empty;

        const union
        {
            const Some<TData> _some;
            const None _none;
        };
    };

    template <class TData>
    struct Left
    {
        Left(TData data) : _data(data) {}

        template <class TFunction>
        auto map(TFunction function) const
        {
            return Left(_data);
        }

        explicit operator Either() const
        {
            return Either(*this);
        }

    private:
        const TData _data;
    };

    template <class TData>
    struct Right
    {
        Right(TData data) : _data(data) {}

        template <class TFunction>
        auto map(TFunction function) const
        {
            return Right(function(_data));
        }

        explicit operator Either() const
        {
            return Either(*this);
        }

    private:
        const TData _data;
    };

    template <class TLeftData, class TRightData>
    struct Either
    {
    private:
        Either(Right<TRightData> right) : _right(right), _is_right(true) {}
        Either(Left<TLeftData> left) : _left(left), _is_right(false) {}

        friend struct Right<TRightData>;
        friend struct Left<TLeftData>;

        const bool _is_right;
        const union
        {
            const Left<TLeftData> _left;
            const Right<TRightData> _right;
        }
    };

    /*
    Either<Connection, Error> connect(std::string Db) {
        if (failed) {
            return Left(new Error)
        } else {
            return Right(new Connection)
        }
    }
    */
}
