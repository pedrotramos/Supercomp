#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <omp.h>

struct Point
{
    double x, y;
};

typedef std::vector<std::default_random_engine> generators;

int main()
{
    int sum = 0;
    int N = 100000;
    std::uniform_real_distribution<double> realDistribution(0.0, 1.0);
    generators gen;
#pragma omp parallel
    {
#pragma omp master
        {
            for (int i = 0; i < omp_get_num_threads(); i++)
            {
                std::default_random_engine generator;
                generator.seed(i);
                gen.push_back(generator);
            }
        }
    }
#pragma omp parallel for reduction(+ \
                                   : sum)
    for (int i = 0; i < N; i++)
    {
        Point p;
        int thread_num = omp_get_thread_num();
        p.x = realDistribution(gen[thread_num]);
        p.y = realDistribution(gen[thread_num]);
        if ((p.x * p.x + p.y * p.y) <= 1)
            sum++;
    }
    std::cerr << sum << std::endl;
    double pi = double(4 * sum) / N;
    std::cout << std::fixed;
    std::cout << std::setprecision(6) << pi << std::endl;
    return 0;
}
