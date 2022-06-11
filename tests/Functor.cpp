#include "doctest.h"

#include <nyan/Functor.h>

#include <string>

///////////////////////////////////////////////////////////////////////////////

auto inc(int x) -> int
{
    return x + 1;
}

auto to_string(int x) -> std::string
{
    return std::to_string(x);
}

///////////////////////////////////////////////////////////////////////////////

template <class T>
class Option
{
public:
    Option(T v) : value_(v), is_empty_(false) {}

    static Option<T> None()
    {
        return Option();
    }

    const T &unwrap() const
    {
        NYAN_ENFORCE(!is_empty());
        return value_;
    }

    bool is_empty() const
    {
        return is_empty_;
    }

private:
    Option() : is_empty_(true) {}

private:
    bool is_empty_;
    T value_;
};

template <class a, class b>
struct nyan::fmap<Option, a, b>
{
    static constexpr bool implemented = true;
    Function<Option<a>, Option<b>> operator()(const Function<a, b> &f) const
    {
        return [&f](const Option<a> &op)
        {
            if (op.is_empty())
            {
                return Option<b>::None();
            }
            else
            {
                return Option(f(op.unwrap()));
            }
        };
    }
};

///////////////////////////////////////////////////////////////////////////////

template <class T>
struct Identity
{
    Identity(const T &v) : val_(v) {}

    const T &get() const { return val_; }

private:
    const T val_;
};

template <class a, class b>
struct nyan::fmap<Identity, a, b>
{
    static constexpr bool implemented = true;
    Function<Identity<a>, Identity<b>> operator()(const Function<a, b> &f) const
    {
        return [&f](const Identity<a> &x)
        {
            return Identity(f(x.get()));
        };
    }
};

///////////////////////////////////////////////////////////////////////////////

template <class T>
struct Dummy
{
};

///////////////////////////////////////////////////////////////////////////////

TEST_CASE("Functor")
{
    SUBCASE("Option")
    {
        SUBCASE("Option::Option(T)")
        {
            const auto op = Option(1);
            CHECK_FALSE(op.is_empty());
            CHECK(op.unwrap() == 1);
        }

        SUBCASE("Option::None()")
        {
            const auto op = Option<int>::None();
            CHECK(op.is_empty());
            CHECK_THROWS(op.unwrap());
        }

        SUBCASE("Option::unwrap()")
        {
            const auto op = Option(1);
            CHECK(op.unwrap() == 1);

            const auto op2 = Option<int>::None();
            CHECK_THROWS(op2.unwrap());
        }

        SUBCASE("Option::is_empty()")
        {
            const auto op = Option(1);
            CHECK_FALSE(op.is_empty());

            const auto op2 = Option<int>::None();
            CHECK(op2.is_empty());
        }

        SUBCASE("fmap")
        {
            const auto op = Option(1);
            const auto e = Option<int>::None();

            SUBCASE("inc")
            {
                const auto inc_op = nyan::fmap<Option, int, int>{}(inc);

                const auto o1 = inc_op(op);
                CHECK_FALSE(o1.is_empty());
                CHECK(o1.unwrap() == 2);

                const auto o2 = inc_op(e);
                CHECK(o2.is_empty());
                CHECK_THROWS(o2.unwrap());
            }

            SUBCASE("to_string")
            {
                const auto to_string_op = nyan::fmap<Option, int, std::string>{}(to_string);

                const auto o3 = to_string_op(op);
                CHECK_FALSE(o3.is_empty());
                CHECK(o3.unwrap() == "1");

                const auto o4 = to_string_op(e);
                CHECK(o4.is_empty());
                CHECK_THROWS(o4.unwrap());
            }
        }

        SUBCASE("map")
        {
            const auto op = Option(1);
            const auto e = Option<int>::None();

            SUBCASE("inc")
            {
                const auto o1 = nyan::map<Option, int, int>(inc, op);
                CHECK_FALSE(o1.is_empty());
                CHECK(o1.unwrap() == 2);

                const auto o2 = nyan::map<Option, int, int>(inc, e);
                CHECK(o2.is_empty());
                CHECK_THROWS(o2.unwrap());
            }

            SUBCASE("to_string")
            {
                const auto o3 = nyan::map<Option, int, std::string>(to_string, op);
                CHECK_FALSE(o3.is_empty());
                CHECK(o3.unwrap() == "1");

                const auto o4 = nyan::map<Option, int, std::string>(to_string, e);
                CHECK(o4.is_empty());
                CHECK_THROWS(o4.unwrap());
            }
        }
    }
}
