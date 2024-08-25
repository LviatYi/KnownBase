#include "Solution26.h"

#pragma region 差速指针法
int Solution26::removeDuplicates(std::vector<int>& nums) {
    int j = 1;
    for (int i = 1; i < nums.size(); i++, j++) {
        if (nums[i] == nums[i - 1]) {
            j--;
        }
        else {
            nums[j] = nums[i];
        }
    }

    return j;
}
#pragma endregion

