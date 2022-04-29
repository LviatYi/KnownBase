#include "Solution35.h"

using namespace std;

int Solution35::searchInsert(std::vector<int>& nums, int target) {
    int start = 0;
    int end = nums.size();
    int mid = (start + end) / 2;

    while (start < end - 1) {
        if (nums[mid] < target) {
            start = mid;
        }
        else {
            end = mid;
        }
        mid = (start + end) / 2;
    }
    if (nums[start] == target || nums[start] > target) {
        return start;
    }
    else {
        return start + 1;
    }
}
