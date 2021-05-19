#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

struct Object
{
    int w, v, index;
    float ratioVW;
    int used;
};

struct Solution
{
    std::vector<float> used;
    float totalValue;
};

typedef std::vector<Object> vetor;

// Reordena os objetos de forma crescente de acordo com o sua razão V/W
vetor sortObjectsByRatio(vetor objs)
{
    std::sort(objs.begin(), objs.end(), [](const Object &o1, const Object &o2) {
        return o1.ratioVW > o2.ratioVW;
    });
    return objs;
}

// Reordena os objetos de forma crescente de acordo com o seu índice
vetor sortObjectsByIndex(vetor objs)
{
    std::sort(objs.begin(), objs.end(), [](const Object &o1, const Object &o2) {
        return o1.index < o2.index;
    });
    return objs;
}

int mochilaFracionaria(int N, int W, vetor &objs, int i, Solution sol)
{
    float value = 0;
    float weight = W;
    for (int j = i; j < N; j++)
    {
        if (weight - objs[i].w >= 0)
        {
            sol.used[i] = 1;
            weight -= objs[i].w;
        }
        else
        {
            sol.used[i] = float(weight) / float(objs[i].w);
            weight = 0;
        }
        value += sol.used[i] * objs[i].v;
    }
    return value;
}

int mochilaBinaria(int N, int W, vetor &objs, int i, float &melhorSolucao, Solution sol, int &num_leaf, int &num_copy, std::vector<int> &bounds, std::vector<float> &melhor)
{
    if (i == N)
    {
        if (sol.totalValue > melhorSolucao)
        {
            melhorSolucao = sol.totalValue;
            melhor = sol.used;
            num_copy++;
        }
        num_leaf++;
        return 0;
    }
    float maxPossivel = 0;
    // Contabiliza usados
    for (int j = 0; j < int(sol.used.size()); j++)
    {
        if (sol.used[j])
        {
            maxPossivel += objs[j].v;
        }
    }
    // Contabiliza faltantes
    maxPossivel += mochilaFracionaria(N, W, objs, i, sol);
    if (maxPossivel <= melhorSolucao)
    {
        bounds[i]++;
        return 0;
    }
    int semItem = mochilaBinaria(N, W, objs, i + 1, melhorSolucao, sol, num_leaf, num_copy, bounds, melhor);
    int comItem = semItem;
    if (W - objs[i].w >= 0)
    {
        sol.used[i] = 1;
        sol.totalValue += objs[i].v;
        comItem = mochilaBinaria(N, W - objs[i].w, objs, i + 1, melhorSolucao, sol, num_leaf, num_copy, bounds, melhor) + objs[i].v;
    }
    return std::max(comItem, semItem);
}

int main()
{
    int N, W, vi, wi;
    std::cin >> N >> W;
    vetor objs;
    Solution sol;
    std::vector<float> best;
    std::vector<int> bounds;
    sol = {std::vector<float>(), 0};
    for (int i = 0; i < N; i++)
    {
        std::cin >> wi >> vi;
        Object objInfo = {wi, vi, i, float(vi) / float(wi), false};
        objs.push_back(objInfo);
        sol.used.push_back(0);
        best.push_back(0);
        bounds.push_back(0);
    }
    objs = sortObjectsByRatio(objs);
    int num_leaf = 0;
    int num_copy = 0;
    float solucao = 0;
    int resp = mochilaBinaria(N, W, objs, 0, solucao, sol, num_leaf, num_copy, bounds, best);
    for (int i = 0; i < N; i++)
    {
        if (best[i])
        {
            objs[i].used = 1;
        }
    }
    objs = sortObjectsByIndex(objs);
    std::cout << "NUM LEAF: " << num_leaf << std::endl;
    std::cout << "NUM COPY: " << num_copy << std::endl;
    for (int i = 0; i < N; i++)
    {
        std::cout << "NUM BOUNDS " << i << ": " << bounds[i] << std::endl;
    }
    std::cout << "RESULTADO: " << resp << std::endl;
    for (int i = 0; i < N; i++)
    {
        std::cout << objs[i].used << " ";
    }
    std::cout << std::endl;
}