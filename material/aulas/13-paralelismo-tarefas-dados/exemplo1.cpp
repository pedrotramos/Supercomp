#include <omp.h>
#include <iostream>

int main() {
    #pragma omp parallel for
    for (int i = 0; i < 16; i++) {
        std::cout << i << " Eu rodei na thread: " << omp_get_thread_num() << "\n";
    }
    return 0;
}