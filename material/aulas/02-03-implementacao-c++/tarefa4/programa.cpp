#include <iostream>
#include <iomanip>

int main()
{
    int n;
    std::cin >> n;
    double var = 0.0;
    double avg = 0.0;
    double sum = 0.0;
    double *x = new double[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> x[i];
        sum += x[i];
    }
    avg = sum / n;
    for (int i = 0; i < n; i++)
    {
        var += (x[i] - avg) * (x[i] - avg);
    }
    delete[] x;
    var /= n;
    std::cout << std::fixed;
    std::cout << std::setprecision(9) << avg << " " << std::setprecision(9) << var << "\n";
    return 0;
}