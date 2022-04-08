#include "Sword39.h"
#include<algorithm>

#pragma region 排序
int Sword39::majorityElement(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    return nums[nums.size() / 2 - 1];
}
#pragma endregion

#pragma region BoyerMoore 投票算法
int Sword39::majorityElement2(vector<int>& nums) {
    int balance = 1;
    int candidate = nums[0];

    for (int i = 1; i < nums.size(); i++) {
        if (balance == 0) {
            candidate = nums[i];
            balance++;
        }
        else if (nums[i] == candidate) {
            balance++;
        }
        else {
            balance--;
        }
    }
    return candidate;
}
#pragma endregion


