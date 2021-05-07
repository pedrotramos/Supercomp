#include <iostream>
#include <iomanip>
#include <random>
#include <omp.h>

struct Point
{
    double x, y;
};

int main()
{
    int sum = 0;
    int N = 100000;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> realDistribution(0.0, 1.0);
#pragma omp parallel for reduction(+ \
                                   : sum)
    for (int i = 0; i < N; i++)
    {
        Point p;
#pragma omp critical
        {
            p.x = realDistribution(generator);
            p.y = realDistribution(generator);
        }
        if ((p.x * p.x + p.y * p.y) <= 1)
            sum++;
    }
    std::cerr << sum << std::endl;
    double pi = double(4 * sum) / N;
    std::cout << std::fixed;
    std::cout << std::setprecision(6) << pi << std::endl;
    return 0;
}
