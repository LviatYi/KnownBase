#pragma once
#include <vector>

class Swordii84 {
private:
    std::vector<std::vector<int>> ans;
    std::vector<int> temp;
    void dfs(std::vector<int>& nums, int* is_chosen);

public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums);
};
