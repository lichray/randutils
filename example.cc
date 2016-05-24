#include "randutils.hpp"
#include <iostream>

int main()
{
	randutils::random_generator rng;
	std::cout << rng.uniform(40, 100) << std::endl;
}
