#include "Swordii40.h"

#include <stack>

int Swordii40::largestRectangleArea(std::vector<int>& heights) {
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

int Swordii40::maximalRectangle(std::vector<std::string>& matrix) {
    int max_area = 0;
    for (int i = 0; i < matrix.size(); ++i) {
        std::vector<int> valid_length = std::vector<int>(matrix[i].size());
        for (int j = 0; j < matrix[i].size(); ++j) {
            for (int k = i; k < matrix.size(); ++k) {
                if (matrix[k][j] == '1') {
                    ++valid_length[j];
                }
                else {
                    break;
                }
            }
        }

        int current_max_area = largestRectangleArea(valid_length);
        max_area = max_area < current_max_area ? current_max_area : max_area;
    }
    return max_area;
}
