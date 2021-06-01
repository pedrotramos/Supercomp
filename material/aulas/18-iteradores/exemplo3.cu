#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include <ctype.h>
#include <vector>
#include <string>

typedef std::vector<double> double_vec;

int main()
{
    double_vec stocks;
    std::string value, prev_val;
    while (true)
    {
        std::getline(std::cin, value);
        if (!isdigit(value[0]))
        {
            break;
        }
        else
        {
            stocks.push_back(std::stod(value));
        }
    }
    thrust::host_vector<double> host(int(stocks.size()));
    host = stocks;
    thrust::device_vector<double> dev(host);
    thrust::device_vector<double> ganho_diario(int(stocks.size()) - 1, 0);

    // ganho diário
    thrust::transform(
        dev.begin() + 1,
        dev.end(),
        dev.begin(),
        ganho_diario.begin(),
        thrust::minus<double>()
    );

    double sumDiffs = thrust::reduce(ganho_diario.begin(), ganho_diario.end(), 0.0, thrust::plus<double>());
    double avgDiffs = sumDiffs / int(stocks.size());

    std::cout << "O ganho médio foi de: US$ " << avgDiffs << std::endl;
}