#include "Solution33.h"

using namespace std;

int Solution33::search(std::vector<int>& nums, int target) {
    // 二分法 寻找断点
    int start = 0;
    int end = nums.size() - 1;
    int mid = nums.size() / 2;

    while (start < end) {
        if (nums[mid] >= nums[start]) {
            // start .. mid 升序。
            if (target >= nums[start] && target <= nums[mid]) {
                // target 于 start .. mid 内。
                end = mid;
            }
            else {
                start = mid + 1;
            }
        }
        else {
            // mid .. end 升序
            if (target >= nums[mid] && target <= nums[end]) {
                // target 于 mid .. end 内。
                start = mid;
            }
            else {
                end = mid - 1;
            }
        }
        mid = (end + start) / 2;
    }

    return nums[mid] == target ? mid : -1;
}
