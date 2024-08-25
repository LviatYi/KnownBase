#include "Sword53.h"

#pragma region Sword53_1
static int binarySearchSmaller(const vector<int>& nums, int target, int begin, int end) {
    if (nums[begin] >= target) {
        return -1;
    }
    if (begin >= end - 1) {
        return begin;
    }

    int mid = (begin + end) / 2;

    if (nums[mid] < target) {
        return binarySearchSmaller(nums, target, mid, end);
    }
    else {
        return binarySearchSmaller(nums, target, begin, mid);
    }
}

static int binarySearchBigger(const vector<int>& nums, int target, int begin, int end) {
    if (nums[end - 1] <= target) {
        return end;
    }
    if (begin >= end - 1) {
        return begin;
    }

    int mid = (begin + end) / 2;

    if (nums[mid - 1] > target) {
        return binarySearchBigger(nums, target, begin, mid);
    }
    else {
        return binarySearchBigger(nums, target, mid, end);
    }
}

int Sword53::search(vector<int>& nums, int target) {
    if (nums.empty()) {
        return 0;
    }
    int smallerPos;
    int biggerPos;

    smallerPos = binarySearchSmaller(nums, target, 0, nums.size());
    biggerPos = binarySearchBigger(nums, target, 0, nums.size());

    return biggerPos - smallerPos - 1;
}
#pragma endregion
#pragma region Sword53_2
int Sword53::missingNumber(vector<int>& nums) {
    if (nums.at(nums.size() - 1) == nums.size() - 1) {
        return nums.size();
    }
    int begin = 0;
    int end = nums.size();
    int mid = (begin + end) / 2;

    while (begin < end - 1) {
        if (nums.at(mid - 1) == mid - 1) {
            begin = mid;
            mid = (begin + end) / 2;
        }
        if (nums.at(mid - 1) > mid - 1) {
            end = mid;
            mid = (begin + end) / 2;
        }
    }
    return begin;
}
#pragma endregion