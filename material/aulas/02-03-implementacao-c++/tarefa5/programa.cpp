#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int main()
{
    int n;
    std::cin >> n;
    double var = 0.0;
    double avg = 0.0;
    double sum = 0.0;
    vector<double> x;
    double val;
    for (int i = 0; i < n; i++)
    {
        std::cin >> val;
        x.push_back(val);
        sum += x[i];
    }
    avg = sum / n;
    for (int i = 0; i < n; i++)
    {
        var += (x[i] - avg) * (x[i] - avg);
    }
    var /= n;
    std::cout << std::fixed;
    std::cout << std::setprecision(9) << avg << " " << std::setprecision(9) << var << "\n";
    return 0;
}