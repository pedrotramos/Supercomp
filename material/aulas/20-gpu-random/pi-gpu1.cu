#include <thrust/device_vector.h>
#include <thrust/random.h>
#include <iostream>
#include <iomanip>
#include <random>

struct inCircle {
    thrust::default_random_engine rng;
    thrust::uniform_real_distribution<double> distribution;

    inCircle(thrust::default_random_engine engine, thrust::uniform_real_distribution<double> dist) {
        rng = engine;
        distribution = dist;
    }

    __device__ __host__
    int operator() (const int &i) {
        rng.seed(i * 100000);
        double x = distribution(rng);
        double y = distribution(rng);
        return (x * x) + (y * y) <= 1 ? 1 : 0;
    }
};

int main()
{
    int N = 100000;
    thrust::default_random_engine generator;
    thrust::uniform_real_distribution<double> realDistribution(0.0, 1.0);
    thrust::device_vector<double> dev(N, 0);
    thrust::counting_iterator<int> iterator(0);
    int sum = thrust::transform_reduce(
        iterator,
        iterator + dev.size(),
        inCircle(generator, realDistribution),
        0, 
        thrust::plus<int>()
    );
    std::cerr << sum << std::endl;
    double pi = double(4 * sum) / N;
    std::cout << std::fixed;
    std::cout << std::setprecision(6) << pi << std::endl;
}
