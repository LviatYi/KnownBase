#include "Swordii76.h"

#include <queue>

#pragma region 优先队列

int Swordii76::findKthLargest(std::vector<int>& nums, int k) {
    std::priority_queue<int, std::vector<int>, std::greater<>> queue = {};

    for (int num : nums) {
        if (queue.size() < k) {
            queue.push(num);
        }
        else if (num > queue.top()) {
            queue.push(num);
            queue.pop();
        }
    }
    return queue.top();
}

#pragma endregion

#pragma region 快速排序

void Swordii76::quick_sort(std::vector<int>& container, int begin, int end, int target) {
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

int Swordii76::findKthLargest2(std::vector<int>& nums, int k) {
    quick_sort(nums, 0, nums.size(), nums.size() - k);
    return nums[nums.size() - k];
}

#pragma endregion
