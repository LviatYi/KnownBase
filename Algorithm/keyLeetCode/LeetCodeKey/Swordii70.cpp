#include "Swordii70.h"

int Swordii70::singleNonDuplicate(std::vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }

    size_t start = 0;
    size_t end = nums.size();
    while (start < end) {
        size_t i = (start + end) / 2;

        if (i >= 1 && nums[i] == nums[i - 1]) {
            if (i % 2) {
                start = i + 1;
            }
            else {
                end = i - 1;
            }
            continue;
        }

        if (i + 1 < nums.size() && nums[i] == nums[i + 1]) {
            if (i % 2) {
                end = i - 1;
            }
            else {
                start = i + 2;
            }
            continue;
        }

        return nums[i];
    }
    return nums[start];
}
