#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

struct Object
{
    int w, v;
};

typedef std::vector<Object> vetor;

int mochilaBinaria(int N, int W, vetor objs, int i)
{
    if (i == N)
    {
        return 0;
    }
    int semItem = mochilaBinaria(N, W, objs, i + 1);
    int comItem = semItem;
    if (W - objs[i].w >= 0)
    {
        comItem = mochilaBinaria(N, W - objs[i].w, objs, i + 1) + objs[i].v;
    }
    return std::max(comItem, semItem);
}

int main()
{
    int N, W, vi, wi;
    std::cin >> N >> W;
    vetor objs;
    for (int i = 0; i < N; i++)
    {
        std::cin >> wi >> vi;
        Object objInfo = {wi, vi};
        objs.push_back(objInfo);
    }
    int resp = mochilaBinaria(N, W, objs, 0);
    std::cout << resp << std::endl;
}