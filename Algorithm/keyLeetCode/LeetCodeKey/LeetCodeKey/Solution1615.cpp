#include "Solution1615.h"

int Solution1615::maximalNetworkRank(int n, std::vector<std::vector<int>>& roads) {
    std::vector<std::vector<bool>> connect(n, std::vector<bool>(n, false));
    std::vector<int> degree(n);
    for (auto road : roads) {
        int x = road[0], y = road[1];
        connect[x][y] = true;
        connect[y][x] = true;
        degree[x]++;
        degree[y]++;
    }

    int first = -1, second = -2;
    std::vector<int> firstArr, secondArr;
    for (int i = 0; i < n; ++i) {
        if (degree[i] > first) {
            second = first;
            secondArr = firstArr;
            first = degree[i];
            firstArr.clear();
            firstArr.emplace_back(i);
        }
        else if (degree[i] == first) {
            firstArr.emplace_back(i);
        }
        else if (degree[i] > second) {
            secondArr.clear();
            second = degree[i];
            secondArr.emplace_back(i);
        }
        else if (degree[i] == second) {
            secondArr.emplace_back(i);
        }
    }
    if (firstArr.size() == 1) {
        int u = firstArr[0];
        for (int v : secondArr) {
            if (!connect[u][v]) {
                return first + second;
            }
        }
        return first + second - 1;
    }
    int m = roads.size();
    if (firstArr.size() * (firstArr.size() - 1) / 2 > m) {
        return first * 2;
    }
    for (int u : firstArr) {
        for (int v : firstArr) {
            if (u != v && !connect[u][v]) {
                return first * 2;
            }
        }
    }
    return first * 2 - 1;
}
