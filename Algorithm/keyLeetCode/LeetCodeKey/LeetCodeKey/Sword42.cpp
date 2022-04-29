#include "Sword42.h"

#pragma region 分治法_算法导论
static int max(int a, int b, int c) {
    if (a > b && a > c) {
        return a;
    }
    else if (b > c) {
        return b;
    }
    else {
        return c;
    }
}

static int maxSubArrayMiddle(vector<int>& nums, int begin, int mid, int end) {
    if (begin >= end) {
        return nums[begin];
    }

    int maxLeft = INT_MIN;
    int maxRight = INT_MIN;

    int l = mid;
    int r = mid + 1;

    int sum = 0;
    while (l >= begin) {
        sum += nums[l];
        if (sum > maxLeft) {
            maxLeft = sum;
        }
        l--;
    }

    sum = 0;
    while (r <= end) {
        sum += nums[r];
        if (sum > maxRight) {
            maxRight = sum;
        }
        r++;
    }

    return maxLeft + maxRight;
}

static int maxSubArrayHeadTail(vector<int>& nums, int begin, int end) {
    if (begin >= end) {
        return nums[begin];
    }

    int mid = (begin + end) / 2;

    int lMax = maxSubArrayHeadTail(nums, begin, mid);
    int rMax = maxSubArrayHeadTail(nums, mid + 1, end);
    int mMax = maxSubArrayMiddle(nums, begin, mid, end);

    return max(lMax, rMax, mMax);
}


int Sword42::maxSubArray(vector<int>& nums) {
    return maxSubArrayHeadTail(nums, 0, nums.size() - 1);
}
#pragma endregion
#pragma region 动态规划
static vector<int> dp;

int Sword42::maxSubArray2(vector<int>& nums) {
    dp.push_back(nums.at(0));
    int max = dp.at(0);

    for (int i = 1; i < nums.size(); i++) {
        dp.push_back(dp.at(i - 1) + nums.at(i) > nums.at(i) ? dp.at(i - 1) + nums.at(i) : nums.at(i));
        if (dp.at(i) > max) {
            max = dp.at(i);
        }
    }
    return max;
}
#pragma endregion
#pragma region 分治法_线段树
static struct Status {
    int lMax;
    int rMax;
    int mMax;
    int allSum;
};

static Status getSubArrayStatus(vector<int>& nums, int begin, int end) {
        Status thisStatus;

        if (begin >= end) {
            thisStatus.lMax = nums[begin];
            thisStatus.rMax = nums[begin];
            thisStatus.mMax = nums[begin];
            thisStatus.allSum = nums[begin];
            return thisStatus;
        }

        int mid = (begin + end) / 2;

        Status lStatus = getSubArrayStatus(nums, begin, mid);
        Status rStatus = getSubArrayStatus(nums, mid + 1, end);

        thisStatus.mMax = max(lStatus.mMax, rStatus.mMax, max(lStatus.rMax, rStatus.lMax, lStatus.rMax + rStatus.lMax));
        thisStatus.allSum = lStatus.allSum + rStatus.allSum;
        thisStatus.lMax = max(lStatus.lMax, lStatus.allSum, lStatus.allSum + rStatus.lMax);
        thisStatus.rMax = max(rStatus.rMax, rStatus.allSum, rStatus.allSum + lStatus.rMax);

        return thisStatus;
}

int Sword42::maxSubArray3(vector<int>& nums) {
    Status s = getSubArrayStatus(nums, 0, nums.size() - 1);
    return max(s.lMax, s.rMax, s.mMax);
}
#pragma endregion