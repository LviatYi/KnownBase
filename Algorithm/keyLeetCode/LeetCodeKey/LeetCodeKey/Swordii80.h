﻿#pragma once
#include <vector>

class Swordii80 {
private:
    std::vector<int> t = {};
    std::vector<std::vector<int>> ret = {};
    void dfs(int index, int n, int k);
public:
    std::vector<std::vector<int>> combine(int n, int k);
};
