#include "Solution31.h"

using namespace std;

#pragma region 正向扫描
// 花里胡哨 实际与官方解法平均性能一致。
// 时间花费更稳定。
// 官方解法更简短。

/// <summary>
/// 以 start 为起始索引倒置矩阵。
/// </summary>
/// <param name="nums"></param>
void reverseNums(vector<int>& nums, int start = 0) {
    for (int i = start, j = nums.size() - 1; i < j; i++, j--) {
        swap(nums[i], nums[j]);
    }
}

/// <summary>
/// 返回指定数组从 start 至数组末尾的子数组的下一个排列。
/// </summary>
/// <param name="nums"></param>
/// <param name="start"></param>
void next(vector<int>& nums, int start = 0) {
    bool isLargest = true;

    int last = INT_MAX;
    int newStart = start;
    // 检测当下数组是否为最大值。
    for (newStart = start; newStart < nums.size(); newStart++) {
        if (last >= nums[newStart]) {
            last = nums[newStart];
        }
        else {
            isLargest = false;
            break;
        }
    }

    if (isLargest && start == 0) {
        // 无位可借。
        // 倒置数组。
        reverseNums(nums);
    }
    else if (isLargest) {
        // 需从 start 前位借位。
        reverseNums(nums, start);
        for (int i = start; i < nums.size(); i++) {
            if (nums[i] > nums[start - 1]) {
                swap(nums[i], nums[start - 1]);
                break;
            }
        }
    }
    else {
        next(nums, newStart);
    }

    return;
}


void Solution31::nextPermutation(std::vector<int>& nums) {
    next(nums);
}
#pragma endregion

