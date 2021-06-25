#include <nyan/nyan.h>
#include <iostream>
#include <cassert>

int main(void)
{

    constexpr auto increment = [](const auto x){ return x + 1; };

    constexpr auto inc_and_double = nyan::compose(
        [](const auto x){ return x * 2; },
        increment
    );

    const auto val = inc_and_double(2);
    if (val != 6) {
        std::printf("Assertion failed: %d != 6", val);
    } else {
        std::printf("All ok!");
    }

    return 0;
}
