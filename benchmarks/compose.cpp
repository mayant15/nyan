#include <nyan/nyan.h>
#include <chrono>

int main(void)
{
    constexpr auto increment = [](const auto x){ return x + 1; };

    constexpr auto inc_and_double = nyan::compose(
        [](const auto x){ return x * 2; },
        increment
    );

    auto start = std::chrono::high_resolution_clock::now();
    int x = 0;
    for (int i = 0; i < 1000000; ++i)
    {
        x = inc_and_double(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto first = (end - start).count() / 1e6;

    start = std::chrono::high_resolution_clock::now();
    int y = 0;
    for (int i = 0; i < 1000000; ++i)
    {
        y = 2 * (i + 1);
    }
    end = std::chrono::high_resolution_clock::now();
    auto second = (end - start).count() / 1e6;

    std::printf("Avg Functional (ns): %f\nAvg Non-functional (ns): %f\nEqual?: %d\n", first, second, (x == y));

    return 0;
}
