#include "Swordii83.h"

void Swordii83::dfs(std::vector<int>& nums, bool* is_chosen) {
    if (temp.size() == nums.size()) {
        ans.push_back(temp);
    }

    for (int i = 0; i < nums.size(); ++i) {
        if (!is_chosen[i]) {
            is_chosen[i] = true;
            temp.push_back(nums[i]);
            dfs(nums, is_chosen);
            is_chosen[i] = false;
            temp.pop_back();
        }
    }
}

std::vector<std::vector<int>> Swordii83::permute(std::vector<int>& nums) {
    bool* is_chosen = new bool[nums.size()]{false};

    dfs(nums, is_chosen);

    return ans;
}
