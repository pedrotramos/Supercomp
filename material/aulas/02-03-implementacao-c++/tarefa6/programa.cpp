#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
using namespace std;

int main()
{
    int n;
    std::cin >> n;
    vector<double> X, Y;
    vector<vector<double>> M;
    double inX, inY, deltaX, deltaY;
    for (int i = 0; i < n; i++)
    {
        std::cin >> inX >> inY;
        X.push_back(inX);
        Y.push_back(inY);
    }
    for (int i = 0; i < n; i++)
    {
        vector<double> line;
        M.push_back(line);
        for (int j = 0; j < n; j++)
        {
            deltaX = X[i] - X[j];
            deltaY = Y[i] - Y[j];
            M[i].push_back(sqrt(deltaX * deltaX + deltaY * deltaY));
            std::cout << std::fixed;
            std::cout << std::setprecision(2) << M[i][j] << " ";
        }
        std::cout << "\n";
    }
    return 0;
}