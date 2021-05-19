#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

struct Object
{
    int w, v;
};

typedef std::vector<Object> vetor;

int mochilaBinaria(int N, int W, vetor &objs, int i, int &melhorSolucao, std::vector<int> usados, int &num_leaf, int &num_copy, std::vector<int> &bounds)
{
    if (i == N)
    {
        num_leaf++;
        return 0;
    }
    int maxPossivel = 0;
    // Contabiliza faltantes
    for (int j = i; j < N; j++)
    {
        maxPossivel += objs[j].v;
    }
    // Contabiliza usados
    for (int j = 0; j < int(usados.size()); j++)
    {
        if (usados[j])
        {
            maxPossivel += objs[j].v;
        }
    }
    if (maxPossivel <= melhorSolucao)
    {
        bounds[i]++;
        return 0;
    }
    int semItem = mochilaBinaria(N, W, objs, i + 1, melhorSolucao, usados, num_leaf, num_copy, bounds);
    int comItem = semItem;
    if (W - objs[i].w >= 0)
    {
        usados[i] = 1;
        comItem = mochilaBinaria(N, W - objs[i].w, objs, i + 1, melhorSolucao, usados, num_leaf, num_copy, bounds) + objs[i].v;
    }
    if (std::max(comItem, semItem) > melhorSolucao)
    {
        num_copy++;
        melhorSolucao = std::max(comItem, semItem);
    }
    return std::max(comItem, semItem);
}

int main()
{
    int N, W, vi, wi;
    std::cin >> N >> W;
    vetor objs;
    std::vector<int> usados;
    std::vector<int> bounds;
    for (int i = 0; i < N; i++)
    {
        std::cin >> wi >> vi;
        Object objInfo = {wi, vi};
        objs.push_back(objInfo);
        usados.push_back(0);
        bounds.push_back(0);
    }
    int num_leaf = 0;
    int num_copy = 0;
    int solucao = 0;
    int resp = mochilaBinaria(N, W, objs, 0, solucao, usados, num_leaf, num_copy, bounds);
    std::cout << "NUM LEAF: " << num_leaf << std::endl;
    std::cout << "NUM COPY: " << num_copy << std::endl;
    for (int i = 0; i < N; i++)
    {
        std::cout << "NUM BOUNDS " << i << ": " << bounds[i] << std::endl;
    }
    std::cout << "RESULTADO: " << resp << std::endl;
}