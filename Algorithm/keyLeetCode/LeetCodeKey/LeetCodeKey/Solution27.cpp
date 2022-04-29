#include "Solution27.h"

#pragma region 差速指针
int Solution27::removeElement(std::vector<int>& nums, int val) {
    int j = 0;
    for (int i = 0; i < nums.size(); i++, j++) {
        if (nums[i] == val) {
            j--;
        }
        else {
            nums[j] = nums[i];
        }
    }

    return j;
}
#pragma endregion

