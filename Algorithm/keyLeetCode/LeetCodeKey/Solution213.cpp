#include "Solution213.h"

int Solution213::sub_rob(std::vector<int>& nums, int start, int end) {
    int size = end - start;
    if (size == 1) {
        return nums[start];
    }

    int first = nums[start], second = std::max(nums[start], nums[start + 1]);
    for (int i = start + 2; i < end; i++) {
        int temp = second;
        second = std::max(first + nums[i], second);
        first = temp;
    }
    return second;
}

int Solution213::rob(std::vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }
    if (nums.size() < 2) {
        return nums[0];
    }

    return std::max(sub_rob(nums, 0, nums.size() - 1), sub_rob(nums, 1, nums.size()));
}
