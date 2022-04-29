#include "Solution41.h"
#pragma region 置换法
int Solution41::firstMissingPositive(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] > 0 && nums[i] <= nums.size() && nums[nums[i] - 1] != nums[i]) {
            std::swap(nums[i], nums[nums[i] - 1]);
            i--;
        }
    }

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }

    return nums.size() + 1;
}
#pragma endregion


#pragma region 位图
// Leetcode 可能由于超空间造成无法分配内存。
void setMap(char* map, int pos) {
    char in = 1;

    in <<= ((pos - 1) % 8);

    map[pos / 8] |= in;
}

bool testMap(char* map, int pos) {
    char in = 1;

    in <<= ((pos - 1) % 8);

    return map[pos / 8] & in;
}
int Solution41::firstMissingPositive2(vector<int>& nums) {
    char* map = new char[268435456]{ 0 };

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] > 0) {
            setMap(map, nums[i]);
        }
    }

    int ans = 1;
    while (ans < 268435456 && testMap(map, ans)) {
        ans++;
    }
    delete[] map;

    return ans;
}

#pragma endregion