#pragma once
#include <vector>

class Solution78 {
private:
    std::vector<int> t = {};
    std::vector<std::vector<int>> ret = {};

    void dfs(std::vector<int>& nums, int index);
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums);
};
