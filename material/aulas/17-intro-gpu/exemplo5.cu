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
    std::string value;
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

    double sumTotal = thrust::reduce(dev.begin(), dev.end(), 0.0, thrust::plus<double>());
    double avg10y = sumTotal / int(stocks.size());

    double sumLastYear = thrust::reduce(dev.end() - 365, dev.end(), 0.0, thrust::plus<double>());
    double avgLastYear = sumLastYear / 365;

    double maxTotal = thrust::reduce(dev.begin(), dev.end(), 0.0, thrust::maximum<double>());
    double minTotal = thrust::reduce(dev.begin(), dev.end(), maxTotal, thrust::minimum<double>());

    double maxLastYear = thrust::reduce(dev.end() - 365, dev.end(), 0.0, thrust::maximum<double>());
    double minLastYear = thrust::reduce(dev.end() - 365, dev.end(), maxLastYear, thrust::minimum<double>());

    std::cout << "Preço médio nos últimos 10 anos: US$ " << avg10y << std::endl;
    std::cout << "Preço máximo e mínimo dos últimos 10 anos: " << std::endl;
    std::cout << "   Máximo -> US$ " << maxTotal << std::endl;
    std::cout << "   Mínimo -> US$ " << minTotal << std::endl;
    std::cout << "Preço médio no último ano: US$ " << avgLastYear << std::endl;
    std::cout << "Preço máximo e mínimo do último ano: " << std::endl;
    std::cout << "   Máximo -> US$ " << maxLastYear << std::endl;
    std::cout << "   Mínimo -> US$ " << minLastYear << std::endl;
}
