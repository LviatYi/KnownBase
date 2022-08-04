#include "Swordii7.h"

#include <algorithm>

vector<vector<int>> Swordii7::threeSum(vector<int>& nums) {
    vector<vector<int>> ret;
    if (nums.size() < 3) {
        return ret;
    }

    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size() - 2; ++i) {
        int l = i + 1, r = nums.size() - 1;
        int target = -nums.at(i);

        if (l < r && target >= nums.at(l)) {
            while (l < r) {
                int sum = nums.at(l) + nums.at(r);
                if (sum < target) {
                    l++;
                }
                else if (sum > target) {
                    r--;
                }
                else {
                    ret.push_back({-target, nums.at(l), nums.at(r--)});
                    int l_last = nums.at(l++);
                    while (l < r && l_last == nums.at(l)) {
                        l++;
                    }
                }
            }
        }
        while (i + 1 < nums.size() && nums.at(i) == nums.at(i + 1)) {
            i++;
        }
    }

    return ret;
}
