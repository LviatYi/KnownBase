#include "Solution18.h"
#include <algorithm>

using namespace std;

vector<vector<int>> Solution18::fourSum(vector<int>& nums, int target) {
    // 双指针法

    vector<vector<int>>ans;
    if (nums.size() < 4) {
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

        for (int second = first + 1, secondLast = 0; second < nums.size() - 2; second++) {
            // 跳过相同数字
            if (second > first + 1 && nums[second] == secondLast) {
                continue;
            }
            else {
                secondLast = nums[second];
            }

            for (int third = second + 1, fourth = nums.size() - 1, thirdLast = INT_MAX; third < fourth; ) {
                // 跳过已匹配完成的相同数字
                if (third > second + 1 && nums[third] == thirdLast) {
                    third++;
                    continue;
                }

                long long currentValue = (long long)nums[first] + nums[second] + nums[third] + nums[fourth];
                // 排序后，与目标值小则前指针右移，反之左移
                // 相等则记录解

                if (currentValue < target) {
                    third++;
                }
                else if (currentValue == target) {
                    ans.push_back({ nums[first],nums[second] ,nums[third] ,nums[fourth] });
                    // 仅匹配成功后记录 last value
                    thirdLast = nums[third];
                    third++;
                }
                else {
                    fourth--;
                }
            }
        }
    }

    return ans;
}
