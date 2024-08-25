#include "Swordii101.h"

#include <iterator>
#include <numeric>
#include <set>

#pragma region 动态规划

bool Swordii101::canPartition(std::vector<int>& nums) {
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2) {
        return false;
    }
    int target = sum >> 1;

    int n = nums.size();
    std::vector dp_sing = std::vector<bool>(target + 1);

    for (int i = 0; i < n; ++i) {
        for (int j = target; j >= 0; --j) {
            if (i - 1 >= 0) {
                dp_sing[j] = dp_sing[j] || (j - nums[i] >= 0 ? dp_sing[j - nums[i]] : false);

            }
            else {
                dp_sing[j] = j == nums[0] || j == 0;
            }
        }
    }

    return dp_sing[target];
}

#pragma endregion
