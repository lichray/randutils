#include "randutils.hpp"

#include <iostream>
#include <cmath>

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

int main()
{
    randutils::random_generator rng;
    std::cout << rng.uniform(40, 100) << '\n';

    rng = std::mt19937_64();
    std::cout << rng.uniform(100, 200) << '\n';

    rng.use<std::mt19937>();
    std::cout << rng.uniform(1000, 2000) << '\n';

    std::vector<double> v(10000);

    rng.generate(begin(v), end(v));
    std::cout << stddev(begin(v), end(v)) << '\n';

    rng.generate(std::normal_distribution<double>(), v);
    std::cout << stddev(begin(v), end(v)) << '\n';

    for (auto& x : v)
        x = rng.variate<double>();
    std::cout << stddev(begin(v), end(v)) << '\n';
}
