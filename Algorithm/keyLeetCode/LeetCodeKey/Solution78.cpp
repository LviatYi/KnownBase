#include "Solution78.h"

void Solution78::dfs(std::vector<int>& nums, int index) {
    if (index == nums.size()) {
        ret.push_back(t);
        return;
    }
    t.push_back(nums[index]);
    dfs(nums, index + 1);
    t.pop_back();
    dfs(nums, index + 1);
}

std::vector<std::vector<int>> Solution78::subsets(std::vector<int>& nums) {
    dfs(nums, 0);
    return ret;
}
