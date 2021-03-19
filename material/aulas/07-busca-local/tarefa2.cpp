#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

struct Object
{
    int w, v, i;
};

typedef std::vector<Object> vetor;

int main()
{
    int N, W, vi, wi;
    std::cin >> N >> W;
    vetor objs;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> realDistribution(0.0, 1.0);
    for (int i = 0; i < N; i++)
    {
        std::cin >> wi >> vi;
        Object objInfo = {wi, vi, i};
        objs.push_back(objInfo);
    }
    // std::sort(objs.begin(), objs.end(), [](const Object &o1, const Object &o2) {
    //     return o1.w < o2.w;
    // });

    int best_outV = 0;
    int best_outW = 0;
    std::vector<int> best_out;
    for (int k = 0; k < 10; k++)
    {
        generator.seed(k);
        int out_v = 0;
        int out_w = 0;
        Object pickedObj;
        std::vector<int> out_index;
        for (int i = 0; i < N; i++)
        {
            pickedObj = objs[i];
            if (out_w + pickedObj.w <= W && realDistribution(generator) > 0.5)
            {
                out_w += pickedObj.w;
                out_v += pickedObj.v;
                out_index.push_back(pickedObj.i);
            }
        }
        if (out_v > best_outV)
        {
            best_outV = out_v;
            best_outW = out_w;
            best_out = out_index;
        }
    }
    std::cout << best_outW << " " << best_outV << " " << 0 << "\n";
    std::sort(best_out.begin(), best_out.end());
    for (int i = 0; i < int(best_out.size()); i++)
    {
        std::cout << best_out[i] << " ";
    }
    std::cout << "\n";
}