#include <thrust/device_vector.h>
#include <thrust/random.h>
#include <iostream>

struct fillRng {
    thrust::uniform_real_distribution<double> distribution;
    thrust::default_random_engine rng;

    fillRng(thrust::uniform_real_distribution<double> dist, thrust::default_random_engine engine) {
        distribution = dist;
        rng = engine;
    }

    __device__ __host__
    double operator() (const int &i) {
        rng.seed(i);
        return distribution(rng);
    }
};

int main()
{
    thrust::uniform_real_distribution<double> dist(25, 40);
    thrust::default_random_engine rng;
    thrust::device_vector<double> dev(10, 0);
    thrust::counting_iterator<int> iterator(0);
    thrust::transform(
        iterator,
        iterator + dev.size(),
        dev.begin(),
        fillRng(dist, rng)
    );
    for (auto i = dev.begin(); i != dev.end(); i++) {
        std::cout << *i << " "; // este acesso é lento! -- GPU
    }
    std::cout << std::endl;
}