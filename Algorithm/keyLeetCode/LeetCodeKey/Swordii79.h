#pragma once
#include <vector>

class Swordii79 {
private:
    std::vector<int> t = {};
    std::vector<std::vector<int>> ret = {};
    void dfs(std::vector<int>& nums, int index);
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums);
};
