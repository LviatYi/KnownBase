#include "Swordii39.h"

#include <stack>

#pragma region 单调栈

int Swordii39::largestRectangleArea(std::vector<int>& heights) {
    if (heights.empty()) {
        return 0;
    }

    const int n = heights.size();

    std::vector<int> left(n);
    std::vector<int> right(n);
    std::stack<int> stack = {};

    for (int i = 0; i < n; ++i) {
        while (!stack.empty() && heights[stack.top()] >= heights[i]) {
            stack.pop();
        }

        left[i] = stack.empty() ? -1 : stack.top();
        stack.push(i);
    }

    while (!stack.empty()) {
        stack.pop();
    }
    for (int i = n - 1; i >= 0; --i) {
        while (!stack.empty() && heights[stack.top()] >= heights[i]) {
            stack.pop();
        }

        right[i] = stack.empty() ? n : stack.top();
        stack.push(i);
    }

    int ret = 0;
    for (int i = 0; i < n; ++i) {
        ret = std::max(ret, (right[i] - left[i] - 1) * heights[i]);
    }
    return ret;
}

#pragma endregion

#pragma region 单调栈 优化

int Swordii39::largestRectangleArea2(std::vector<int>& heights) {
    if (heights.empty()) {
        return 0;
    }
    int n = heights.size();
    std::vector<int> left(n), right(n, n);

    std::stack<int> mono_stack;
    for (int i = 0; i < n; ++i) {
        while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
            right[mono_stack.top()] = i;
            mono_stack.pop();
        }
        left[i] = (mono_stack.empty() ? -1 : mono_stack.top());
        mono_stack.push(i);
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = std::max(ans, (right[i] - left[i] - 1) * heights[i]);
    }
    return ans;
}

#pragma endregion
