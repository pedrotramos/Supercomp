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
    printf("Device vector: ");
    for (auto i = dev.begin(); i != dev.end(); i++)
    {
        std::cout << *i << " "; // este acesso é lento! -- GPU
    }
    printf("\n");
}
