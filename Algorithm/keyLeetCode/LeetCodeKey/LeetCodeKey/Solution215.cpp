#include "Solution215.h"

void Solution215::quick_sort(std::vector<int>& container, int begin, int end, int target) {
    if (begin >= end - 1) {
        return;
    }
    int i = begin + 1;
    int p_max_left_index = end;

    while (i < p_max_left_index) {
        if (container[i] > container[begin]) {
            int t = container[i];
            container[i] = container[p_max_left_index - 1];
            container[p_max_left_index - 1] = t;
            --p_max_left_index;
        }
        else {
            ++i;
        }
    }
    int t = container[begin];
    container[begin] = container[p_max_left_index - 1];
    container[p_max_left_index - 1] = t;
    --p_max_left_index;

    if (p_max_left_index == target) {
        return;
    }
    if (p_max_left_index > target) {
        quick_sort(container, begin, p_max_left_index, target);
    }
    else {
        quick_sort(container, p_max_left_index + 1, end, target);
    }
}

int Solution215::findKthLargest(std::vector<int>& nums, int k) {
    quick_sort(nums, 0, nums.size(), nums.size() - k);
    return nums[nums.size() - k];
}
