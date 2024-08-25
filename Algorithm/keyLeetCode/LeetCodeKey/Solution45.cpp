#include "Solution45.h"

int Solution45::jump(std::vector<int>& nums) {
    auto dp = std::vector<int>(nums.size(), 0);
    for (int num_index_r = nums.size() - 2;
         num_index_r >= 0;
         --num_index_r) {
        auto const step_len = nums[num_index_r];
        int min_cost = INT_MAX;
        for (int len = 1;
             len <= step_len && num_index_r + len < nums.size();
             ++len) {
            if (dp[num_index_r + len] == -1) {
                continue;
            }
            if (min_cost > dp[num_index_r + len]) {
                min_cost = dp[num_index_r + len];
            }
        }

        if (min_cost == INT_MAX) {
            dp[num_index_r] = -1;
        } else {
            dp[num_index_r] = min_cost + 1;
        }
    }

    return dp[0];
}

int Solution45::jump2(std::vector<int>& nums) {
    if (nums.size() <= 1)return 0;
    int min_step = 1;
    int curr_step_reach = nums[0];
    int next_step_reach = 0;
    for (int num_i = 1; num_i < nums.size(); ++num_i) {
        if (num_i > curr_step_reach) {
            ++min_step;
            curr_step_reach = next_step_reach;
            next_step_reach = 0;
        }
        if (num_i + nums[num_i] > next_step_reach) {
            next_step_reach = num_i + nums[num_i];
        }
    }
    return min_step;
}
