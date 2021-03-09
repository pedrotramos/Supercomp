#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

typedef std::vector<double> vetor;

void calcula_distancias(vetor &v_out, vetor &x, vetor &y)
{
    int n = x.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            double dx = x[i] - x[j];
            double dy = y[i] - y[j];
            double delta = dx * dx + dy * dy;
            v_out[i * n + j] = delta;
            v_out[j * n + i] = delta;
        }
    }
}

int main()
{
    vetor out, x, y;
    int n;

    std::cin >> n;
    x.reserve(n);
    y.reserve(n);
    out.reserve(n * n);
    for (int i = 0; i < n; i++)
    {
        double xt, yt;
        std::cin >> xt >> yt;
        x.push_back(xt);
        y.push_back(yt);
    }

    calcula_distancias(out, x, y);

    int count = 0;
    for (int i = 0; i < n * n; i++)
    {
        std::cout << std::fixed;
        std::cout << std::setprecision(2) << out[i] << " ";
        count++;
        if (count >= n)
        {
            std::cout << "\n";
            count = 0;
        }
    }

    return 0;
}