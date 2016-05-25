#include "randutils.hpp"

#include <iostream>
#include <cmath>
#include <chrono>

template <typename Iter>
auto stddev(Iter first, Iter last)
{
    using T = typename std::iterator_traits<Iter>::value_type;

    auto sum = std::accumulate(first, last, T());
    auto n = std::distance(first, last);
    auto m = sum / n;
    auto accum = std::accumulate(first, last, T(), [=](T v, T d)
                                 {
                                     return v + (d - m) * (d - m);
                                 });

    return std::sqrt(accum / n);
}

template <typename Timepoint>
void show_elapsed(Timepoint a, Timepoint b)
{
    using namespace std::chrono;
    std::cout << ": " << duration_cast<duration<double>>(b - a).count()
              << "s\n";
}

int main()
{
    using namespace std::chrono;

    randutils::random_generator rng;
    std::cout << rng.uniform(40, 100) << '\n';

    rng = std::mt19937_64();
    std::cout << rng.uniform(100, 200) << '\n';

    rng.use<std::mt19937>();
    std::cout << rng.uniform(1000, 2000) << '\n';

    std::vector<double> v(100000);

    rng.generate(begin(v), end(v));
    std::cout << stddev(begin(v), end(v)) << '\n';

    {
        std::cout << "type-erased generate\n";
        auto a = steady_clock::now();
        rng.generate(std::normal_distribution<double>(), v);
        auto b = steady_clock::now();
        show_elapsed(a, b);
        std::cout << stddev(begin(v), end(v)) << '\n';
    }

    {
        std::cout << "type-erased variate\n";
        auto a = steady_clock::now();
        for (auto& x : v)
            x = rng.variate(std::normal_distribution<double>());
        auto b = steady_clock::now();
        show_elapsed(a, b);
        std::cout << stddev(begin(v), end(v)) << '\n';
    }

    {
        std::cout << "type-erased Gaussian\n";
        auto a = steady_clock::now();
        for (auto& x : v)
            x = rng.gauss(0.0, 1.0);
        auto b = steady_clock::now();
        show_elapsed(a, b);
        std::cout << stddev(begin(v), end(v)) << '\n';
    }

    {
        std::mt19937 g(randutils::auto_seed_256().base());
        // warm up
        for (size_t i = 0; i < v.size(); ++i)
            g();
        std::cout << "direct generate\n";
        auto a = steady_clock::now();
        std::normal_distribution<double> d;
        std::generate(begin(v), end(v), [&]
                      {
                          return d(g);
                      });
        auto b = steady_clock::now();
        show_elapsed(a, b);
        std::cout << stddev(begin(v), end(v)) << '\n';
    }
}
