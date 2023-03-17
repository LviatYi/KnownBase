#include "SortUtil.h"

#include <algorithm>

namespace LviatAlgoExtract {
    void SortUtil::quick_sort(std::vector<int>& nums, int begin, int end) {
        if (nums.empty() || begin < 0 || end > nums.size() || end - begin <= 1) {
            return;
        }

        int pivot = nums[begin];
        int high_left_bound = end;
        for (int i = 1; i < end; ++i) {
            if (nums[i] <= pivot) {
                if (high_left_bound != end) {
                    std::swap(nums[i], nums[high_left_bound]);
                    ++high_left_bound;
                }
            }
            else if (high_left_bound == end) {
                high_left_bound = i;
            }
        }

        std::swap(nums[begin], nums[high_left_bound - 1]);
        quick_sort(nums, begin, high_left_bound - 1);
        quick_sort(nums, high_left_bound, end);
    }
}
