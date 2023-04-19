#include "Swordii102.h"

#include <numeric>

int Swordii102::findTargetSumWays(std::vector<int>& nums, int target) {
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    if ((target + sum) % 2 || sum - target < 0 || target + sum < 0) {
        return 0;
    }

    int p_sum = (target + sum) >> 1;

    std::vector<int> dp = std::vector<int>(p_sum + 1, 0);

    for (int i = 0; i < nums.size(); ++i) {
        for (int j = p_sum; j >= 0; --j) {
            if (i != 0) {
                dp[j] += j - nums[i] >= 0 ? dp[j - nums[i]] : 0;
            }
            else {
                if (j == 0) {
                    dp[j] += 1;
                }
                dp[j] += j == nums[i];
            }
        }
    }

    return dp[p_sum];
}
