#include "Solution11.h"

int Solution11::maxArea(vector<int>& height) {
    // 丑陋的虚假动态规划。并未提高性能。
    vector<vector<int>> f(height.size(), vector<int>(height.size()));
    for (int l = 1; l <= height.size(); l++) {
        for (int i = 0; i < height.size() - l; i++) {
            int currentArea = l * (height[i] < height[i + l] ? height[i] : height[i + l]);
            int containMaxArea = 0;
            if (l > 1) {
                containMaxArea = f[i + 1][i + l] > f[i][i + l - 1] ? f[i + 1][i + l] : f[i][i + l - 1];
            }
            f[i][i + l] = containMaxArea > currentArea ? containMaxArea : currentArea;
        }
    }
    return f[0][height.size() - 1];
}

int Solution11::maxArea2(vector<int>& height) {
    // 双指针法

    int maxAreaCount = 0;
    int left = 0;
    int right = height.size() - 1;

    while (left < right) {
        int currentArea = (height[left] < height[right] ? height[left] : height[right]) * (right - left);
        maxAreaCount = maxAreaCount > currentArea ? maxAreaCount : currentArea;

        if (height[left] < height[right]) {
            left++;
        }
        else {
            right--;
        }
    }

    return maxAreaCount;
}
