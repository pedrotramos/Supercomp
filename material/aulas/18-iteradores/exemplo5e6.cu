#include <vector>
#include <string>
#include <ctype.h>
#include <iostream>
#include <thrust/count.h>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/execution_policy.h>


struct is_negative
{
  __host__ __device__
  bool operator()(const double &x)
  {
    return x < 0;
  }
};

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

    int count = thrust::count_if(thrust::device, ganho_diario.begin(), ganho_diario.end(), is_positive());

    thrust::replace_if(thrust::device, ganho_diario.begin(), ganho_diario.end(), is_negative(), 0);
    double sumOfPositives = thrust::reduce(ganho_diario.begin(), ganho_diario.end(), 0.0, thrust::plus<double>());
    double result = sumOfPositives / count;

    std::cout << "O ganho médio foi de: US$ " << result << std::endl;
}