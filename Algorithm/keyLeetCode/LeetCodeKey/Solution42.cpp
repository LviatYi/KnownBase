#include "Solution42.h"

#pragma region 双指针
int Solution42::trap(vector<int>& height) {
    int sum = 0;
    int left = *(height.begin());
    int right = *(height.end() - 1);

    int i = 1;
    int j = height.size() - 2;

    while (i - 1 < j + 1) {
        while (left <= right && i <= j + 1) {
            if (left <= height[i]) {
                left = height[i];
            }
            else {
                sum += left - height[i];
            }
            i++;
        }
        while (right <= left && i - 1 <= j) {
            if (right <= height[j]) {
                right = height[j];
            }
            else {
                sum += right - height[j];
            }
            j--;
        }
    }

    return sum;
}
#pragma endregion
#pragma region 单调栈
#include <stack>
#include <cmath>

using std::stack;
using std::min;
int Solution42::trap2(vector<int>& height) {
        stack<int> leftPeakPos;
        int sum = 0;
        int currVol = 0;

        for (int i = 0; i < height.size(); i++) {
            while (!leftPeakPos.empty() && height.at(leftPeakPos.top()) < height[i]) {
                int leftPos = leftPeakPos.top();
                leftPeakPos.pop();

                if (leftPeakPos.empty()) {
                    break;
                }
                int leftPosPre = leftPeakPos.top();

                sum += (min(height[leftPosPre], height[i]) - height[leftPos]) * (i - leftPos);
            }
            leftPeakPos.push(i);
        }
        return sum;
    }
#pragma endregion
