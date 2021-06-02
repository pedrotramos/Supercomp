#include <thrust/device_vector.h>
#include <thrust/iterator/counting_iterator.h>
#include "imagem.hpp"

struct media {
    unsigned char *p;
    int width, height;

    media (unsigned char *pointer, int w, int h) {
        p = pointer;
        width = w;
        height = h;
    };

    __host__ __device__
    unsigned char operator() (const int &i) {
        int x = i % width;
        int y = i / width;

        unsigned char current = p[y * width + x];
        unsigned char up = y - 1 >= 0 ? p[(y - 1) * width + x] : 0;
        unsigned char down = y + 1 <= height ? p[(y + 1) * width + x] : 0;
        unsigned char left = x - 1 >= 0 ? p[y * width + (x - 1)] : 0;
        unsigned char right = x + 1 <= width ? p[y * width + (x + 1)] : 0;
        return (current + up + down + right + left) / 5;
    }
};

int main() {
    Imagem img = Imagem::read("image.pgm");

    thrust::device_vector<unsigned char> input(img.pixels, img.pixels + img.total_size);
    thrust::device_vector<unsigned char> output(img.total_size);

    thrust::counting_iterator<int> iterator(0);

    thrust::transform(
        iterator,
        iterator + input.size(),
        output.begin(),
        media(thrust::raw_pointer_cast(input.data()), img.cols, img.rows)
    );

    thrust::copy(output.begin(), output.end(), img.pixels);
    img.write("image_media.pmg");
}
