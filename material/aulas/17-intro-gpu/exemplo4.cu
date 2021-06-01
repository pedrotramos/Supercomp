#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include <ctype.h>
#include <vector>
#include <string>
#include <chrono>

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
    auto start = std::chrono::high_resolution_clock::now();
    thrust::device_vector<double> dev(host);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    printf("Device vector: ");
    for (auto i = dev.begin(); i != dev.end(); i++)
    {
        std::cout << *i << " "; // este acesso é lento! -- GPU
    }
    printf("\n");
    std::cerr << duration.count() << "ms" << std::endl;
}
