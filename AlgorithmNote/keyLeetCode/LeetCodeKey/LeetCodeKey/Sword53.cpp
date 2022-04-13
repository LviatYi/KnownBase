#include "Sword53.h"

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