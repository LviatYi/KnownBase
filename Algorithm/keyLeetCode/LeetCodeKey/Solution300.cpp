#include "Solution300.h"

int Solution300::lengthOfLIS(std::vector<int>& nums) {
    int max = 1;
    std::vector<int> dp(nums.size(), 1);

    for (int index = 1; index < nums.size(); ++index) {
        const auto num = nums[index];

        for (int up_index = index - 1; up_index >= 0; --up_index) {
            if (nums[up_index] < num) {
                if (dp[index] < dp[up_index] + 1) {
                    dp[index] = dp[up_index] + 1;
                }
            }
        }

        if (dp[index] > max)max = dp[index];
    }

    return max;
}
