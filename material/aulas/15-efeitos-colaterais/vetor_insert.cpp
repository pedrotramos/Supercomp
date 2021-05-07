#include <vector>
#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <unistd.h>

double conta_complexa(int i)
{
	sleep(1);
	return 2 * i;
}

int main()
{
	int N = 100;
	std::vector<double> vec;
	vec.reserve(vec.size() + N);
#pragma omp parallel for
	for (int i = 0; i < N; i++)
	{
		double val = conta_complexa(i);
		vec[i] = val;
	}

	for (int i = 0; i < N; i++)
	{
		std::cout << i << " ";
	}

	return 0;
}
