#include "randutils.hpp"
#include <iostream>

int main()
{
    randutils::random_generator rng;
    std::cout << rng.uniform(40, 100) << '\n';

    rng = std::mt19937_64();
    std::cout << rng.uniform(100, 200) << '\n';

    rng.use<std::mt19937>();
    std::cout << rng.uniform(1000, 2000) << '\n';
}
