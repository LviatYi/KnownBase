#include "Solution15.h"
#include <algorithm>

using namespace std;

vector<vector<int>> Solution15::threeSum(vector<int>& nums) {
    // 双指针法

    vector<vector<int>>ans;
    if (nums.size() < 3) {
        return ans;
    }

    // 排序
    sort(nums.begin(), nums.end());

    for (int first = 0, firstLast = 0; first < nums.size() - 2; first++) {
        // 跳过相同数字
        if (first > 0 && nums[first] == firstLast) {
            continue;
        }
        else {
            firstLast = nums[first];
        }

        for (int second = first + 1, third = nums.size() - 1, secondLast = INT_MAX; second < third; ) {
            // 跳过已匹配完成的相同数字
            if (second > first + 1 && nums[second] == secondLast) {
                second++;
                continue;
            }

            int currentValue = nums[first] + nums[second] + nums[third];
            // 排序后，与目标值小则前指针右移，反之左移
            // 相等则记录解

            if (currentValue < 0) {
                second++;
            }
            else if (currentValue == 0) {
                ans.push_back({ nums[first] ,nums[second] ,nums[third] });
                // 仅匹配成功后记录 last value
                secondLast = nums[second];
                second++;
            }
            else {
                third--;
            }
        }
    }

    return ans;
}
