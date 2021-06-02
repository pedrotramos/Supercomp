#include <thrust/random.h>
#include <iostream>

int main()
{
    int seed;
    std::cin >> seed;
    thrust::default_random_engine rng;
    thrust::uniform_real_distribution<double> dist(25, 40);
    rng.discard(seed);
    double rng_value = dist(rng);
    std::cout << "Valor gerado: " << rng_value << std::endl;
    return 0;
}