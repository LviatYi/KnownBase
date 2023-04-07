#pragma once
#include <set>
#include <vector>

class Swordii81 {
private:
    std::vector<int> t = {};
    std::vector<std::vector<int>> ret = {};
    void dfs(std::vector<int>& candidates, int target, int min_index);

public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target);
};
