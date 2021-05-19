#include <iostream>
#include <iomanip>

int main()
{
    int n;
    std::cin >> n;
    double denom;
    double resp = 0.0;
    for (int i = 0; i < n; i++)
    {
        denom = 1.0;
        for (int j = 0; j < i; j++)
        {
            denom *= 2;
        }
        resp += 1 / denom;
    }
    std::cout << std::fixed;
    std::cout << std::setprecision(15) << resp << "\n";
    return 0;
}