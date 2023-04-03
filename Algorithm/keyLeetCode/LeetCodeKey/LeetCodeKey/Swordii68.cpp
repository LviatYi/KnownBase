#include "Swordii68.h"

int Swordii68::searchInsert(std::vector<int>& nums, int target) {
    if (nums.empty()) {
        return 0;
    }

    size_t start = 0;
    size_t end = nums.size();
    while (start < end) {
        size_t i = (start + end) / 2;
        if (nums[i] == target) {
            return static_cast<int>(i);
        }

        if (nums[i] > target) {
            end = i;
        }
        else {
            start = i + 1;
        }

    }

    return start;
}
