#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include "imagem.hpp"

struct limiar {
    int size;

    limiar(int n) {
        size = n;
    };

    __host__ __device__
    unsigned char operator() (const unsigned char &p) {
        return p > 127 ? 255 : 0;
    }
};

int main()
{
    Imagem img = Imagem::read("image.pgm");

    thrust::device_vector<unsigned char> dev(img.pixels, img.pixels + img.total_size);

    thrust::transform(
        dev.begin(),
        dev.end(),
        dev.begin(),
        limiar(img.total_size)
    );

    thrust::copy(dev.begin(), dev.end(), img.pixels);
    img.write("image_limiar.pgm");
}