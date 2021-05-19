#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <time.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

void calcula_distancias(vector<double> &X, vector<double> &Y, vector<vector<double>> &M)
{
    int n;
    std::cin >> n;
    double inX, inY;
    for (int i = 0; i < n; i++)
    {
        std::cin >> inX >> inY;
        X.push_back(inX);
        Y.push_back(inY);
    }
    for (int i = 0; i < n; i++)
    {
        double deltaX, deltaY;
        vector<double> line;
        M.push_back(line);
        for (int j = 0; j < n; j++)
        {
            deltaX = X[i] - X[j];
            deltaY = Y[i] - Y[j];
            M[i].push_back(sqrt(deltaX * deltaX + deltaY * deltaY));
        }
    }
    return;
}

int main()
{
    auto t1 = high_resolution_clock::now();
    vector<double> X, Y;
    vector<vector<double>> M;
    calcula_distancias(X, Y, M);
    for (int i = 0; i < int(X.size()); i++)
    {
        for (int j = 0; j < int(X.size()); j++)
        {
            std::cout << std::fixed;
            std::cout << std::setprecision(2) << M[i][j] << " ";
        }
        std::cout << "\n";
    }
    auto t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1);
    std::cout << "Time taken: " << duration.count() << "ms" << std::endl;
    return 0;
}