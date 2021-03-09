#include <iostream>
#include <algorithm>
#include <vector>

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
    for (int i = 0; i < N; i++)
    {
        std::cin >> wi >> vi;
        Object objInfo = {wi, vi, i};
        objs.push_back(objInfo);
    }
    std::sort(objs.begin(), objs.end(), [](const Object &o1, const Object &o2) {
        return o1.w < o2.w;
    });
    int out_v = 0;
    int out_w = 0;
    std::vector<int> out_index;
    for (int i = 0; i < N; i++)
    {
        if (out_w + objs[i].w <= W)
        {
            out_w += objs[i].w;
            out_v += objs[i].v;
            out_index.push_back(objs[i].i);
        }
    }
    std::cout << out_w << " " << out_v << " " << 0 << "\n";
    std::sort(out_index.begin(), out_index.end());
    for (int i = 0; i < int(out_index.size()); i++)
    {
        std::cout << out_index[i] << " ";
    }
    std::cout << "\n";
}