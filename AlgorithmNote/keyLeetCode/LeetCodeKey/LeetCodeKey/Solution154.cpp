#include "Solution154.h"

int Solution154::findMin(vector<int>& nums) {
    int begin = 0;
    int end = nums.size() - 1;
    // 避免溢出
    int mid = begin + (end - begin) / 2;

    while (mid < end) {
        if (nums[mid] > nums[end]) {
            begin = mid + 1;
        }
        else if (nums[mid] < nums[end]) {
            end = mid;
        }
        else {
            end--;
        }

        mid = (begin + end) / 2;

    }

    return nums[0] < nums[end] ? nums[0] : nums[end];
}
