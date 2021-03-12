#include <iostream>
#include <random>

int main()
{
    std::random_device rd;                        // obtain a random number from hardware
    std::mt19937 gen(rd());                       // seed the generator
    std::uniform_int_distribution<> distr(-2, 5); // define the range

    std::cout << distr(gen) << std::endl; // generate numbers
    return 0;
}