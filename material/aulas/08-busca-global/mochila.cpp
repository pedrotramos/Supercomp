#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

struct Object
{
    int w, v;
};

typedef std::vector<Object> vetor;

int mochilaBinaria(int N, int W, vetor objs, int i, int &num_leaf)
{
    if (i == N)
    {
        num_leaf++;
        return 0;
    }
    int semItem = mochilaBinaria(N, W, objs, i + 1, num_leaf);
    int comItem = semItem;
    if (W - objs[i].w >= 0)
    {
        comItem = mochilaBinaria(N, W - objs[i].w, objs, i + 1, num_leaf) + objs[i].v;
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
    int num_leaf = 0;
    int resp = mochilaBinaria(N, W, objs, 0, num_leaf);
    std::cout << "NUM LEAF: " << num_leaf << std::endl;
    std::cout << resp << std::endl;
}