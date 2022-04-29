#include "Solution16.h"

#include <algorithm>
#include <math.h>

int Solution16::threeSumClosest(vector<int>& nums, int target) {
    // 双指针法

    // 排序
    sort(nums.begin(), nums.end());

    int distance = INT_MAX;

    for (int first = 0; first < nums.size() - 2; first++) {
        for (int second = first + 1, third = nums.size() - 1; second < third;) {
            int currentDistance = nums[first] + nums[second] + nums[third] - target;

            distance = abs(distance) < abs(currentDistance) ? distance : currentDistance;

            // 排序后，与目标值小则前指针右移，反之左移
            if (currentDistance < 0) {
                second++;
            }
            else if (currentDistance == 0) {
                break;
            }
            else {
                third--;
            }
        }
        if (!distance) {
            break;
        }
    }
    return target + distance;
}
