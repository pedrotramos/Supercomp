#include <thrust/random.h>
#include <iostream>

int main()
{
    int seed;
    std::cin >> seed;
    thrust::default_random_engine rng;
    thrust::uniform_int_distribution<int> dist(20, 45);
    rng.discard(seed);
    for (int i = 0; i < 10; i++)
    {
        int rng_value = dist(rng);
        std::cout << rng_value << " ";
    }
    std::cout << std::endl;
    return 0;
}