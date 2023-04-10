#pragma once
#include <vector>

class Solution46 {
private:
    std::vector<std::vector<int>> ans;
    std::vector<int> temp;
    void dfs(std::vector<int>& nums, bool* is_chosen);

public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums);
};
