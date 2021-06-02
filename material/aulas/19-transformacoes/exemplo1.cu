#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include <ctype.h>
#include <vector>
#include <string>

struct CalcVar {
    double avg;
    int size;

    CalcVar(double a, int n) {
        avg = a;
        size = n;
    };

    __host__ __device__
    double operator()(const double& x) {
        return ((x - avg) * (x - avg)) / size;
    }
};

typedef std::vector<double> double_vec;

int main()
{
    double_vec aapl, msft;
    std::string values;
    std::string delimiter = " ";
    while (true)
    {
        std::getline(std::cin, values);
        if (!isdigit(values[0]))
        {
            break;
        }
        else
        {
            std::string first_val = values.substr(0, values.find(delimiter));
            aapl.push_back(std::stod(first_val));
            std::string second_val = values.erase(0, values.find(delimiter) + delimiter.length());
            msft.push_back(std::stod(second_val));
        }
    }
    thrust::host_vector<double> host_aapl(int(aapl.size())), host_msft(int(msft.size()));
    host_aapl = aapl;
    host_msft = msft;
    thrust::device_vector<double> dev_aapl(host_aapl), dev_msft(host_msft), dev(int(aapl.size()), 0);

    thrust::transform(
        dev_aapl.begin(),
        dev_aapl.end(),
        dev_msft.begin(),
        dev.begin(),
        thrust::minus<double>()
    );

    double sumDiffs = thrust::reduce(dev.begin(), dev.end(), 0.0, thrust::plus<double>());
    double avgDiffs = sumDiffs / int(aapl.size());

    double variance = thrust::transform_reduce(
        dev.begin(), 
        dev.end(), 
        CalcVar(avgDiffs, int(aapl.size())), 
        0.0, 
        thrust::plus<double>()
    );

    std::cout << "A variância da diferença entre AAPL e MSFT nos últimos 10 anos: US$ " << variance << std::endl;
}