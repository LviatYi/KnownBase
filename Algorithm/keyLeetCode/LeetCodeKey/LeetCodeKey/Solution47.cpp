#include "Solution47.h"

void Solution47::dfs(std::vector<int>& nums, int* is_chosen) {
    if (temp.size() == nums.size()) {
        ans.push_back(temp);
    }

    for (int i = 0; i < 21; ++i) {
        int current_val = i - 10;
        int* p_current_index_chosen = is_chosen + i;

        if (*p_current_index_chosen > 0 && (temp.empty() || current_val != temp.back())) {
            int j = 0;
            int count = *p_current_index_chosen;
            for (; j < count; ++j) {
                --(*p_current_index_chosen);
                temp.push_back(current_val);
                dfs(nums, is_chosen);
            }
            while (j--) {
                ++(*p_current_index_chosen);
                temp.pop_back();
            }
        }
    }
}

std::vector<std::vector<int>> Solution47::permuteUnique(std::vector<int>& nums) {
    int* is_chosen = new int[21]{0};

    for (auto num : nums) {
        ++is_chosen[num + 10];
    }

    dfs(nums, is_chosen);

    return ans;
}
