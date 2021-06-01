#include <vector>
#include <string>
#include <ctype.h>
#include <iostream>
#include <thrust/count.h>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/execution_policy.h>


struct is_positive
{
  __host__ __device__
  bool operator()(const double &x)
  {
    return x > 0;
  }
};

typedef std::vector<double> double_vec;

int main(){
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

    // count the positive elements in ganho_diario
    int result = thrust::count_if(thrust::device, ganho_diario.begin(), ganho_diario.end(), is_positive());
    std::cout << "O número de variações positivas foi: " << result << std::endl;
}