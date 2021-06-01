#include <thrust/random.h>
#include <iostream>

int main()
{
    int seed;
    std::cin >> seed;
    thrust::default_random_engine rng;
    thrust::uniform_int_distribution<int> dist(20, 45);
    rng.discard(seed);
    int rng_value = dist(rng);
    std::cout << "Valor gerado: " << rng_value << std::endl;
    return 0;
}