#include "Solution198.h"

#pragma region 动态规划

int Solution198::rob(std::vector<int>& nums) {
    if (nums.size() <= 2) {
        if (nums.size() == 1) {
            return nums[0];
        }

        return std::max(nums[0], nums[1]);
    }

    std::vector<int> _dp;
    _dp.reserve(nums.size() + 1);

    _dp.push_back(nums[0]);
    _dp.push_back(nums[1]);

    for (int i = 2; i <= nums.size(); ++i) {
        _dp.push_back(
            (i < nums.size() ? nums[i] : 0) + std::max(i - 2 >= 0 ? _dp[i - 2] : 0, i - 3 >= 0 ? _dp[i - 3] : 0)
        );
    }

    return std::max(_dp[nums.size() - 1], _dp[nums.size()]);
}

#pragma endregion

#pragma region 滚动数组

int Solution198::rob2(std::vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }
    int size = nums.size();
    if (size == 1) {
        return nums[0];
    }
    int first = nums[0], second = std::max(nums[0], nums[1]);
    for (int i = 2; i < size; i++) {
        int temp = second;
        second = std::max(first + nums[i], second);
        first = temp;
    }
    return second;
}

#pragma endregion
