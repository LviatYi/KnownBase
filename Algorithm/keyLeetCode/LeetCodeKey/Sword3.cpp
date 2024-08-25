#include "Sword3.h"
#include<unordered_set>

using std::unordered_set;

int Sword3::findRepeatNumber(vector<int>& nums) {
    unordered_set<int> set;
    for (int num : nums) {
        if (!set.insert(num).second) {
            return num;
        }
    }

    return 0;
}

int Sword3::findRepeatNumber2(vector<int>& nums) {
    int t;
    for (int i = 0; i < nums.size(); ++i) {
        while (nums[i] != i) {
            if (nums[i] == nums[nums[i]]) {
                return nums[i];
            }
            t = nums[i];
            nums[i] = nums[t];
            nums[t] = t;
        }
    }
    return 0;
}
