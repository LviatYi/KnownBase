#include "Solution32.h"
#include <vector>
#include <stack>

using namespace std;

#pragma region 动态规划
int Solution32::longestValidParentheses(std::string s) {
    vector<int> dp;
    if (s.size() == 0) {
        return 0;
    }
    int balance = s[0] == '(' ? 1 : 0;
    int maxCount = 0;
    dp.push_back(0);
    for (int i = 1; i < s.size(); i++) {
        if (s[i] == '(') {
            balance++;
            dp.push_back(0);
        }
        else if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(') {
            // 对应有 ( 匹配
            if (i - dp[i - 1] - 2 > 0) {
                dp.push_back(dp[i - 1] + 2 + dp[i - dp[i - 1] - 2]);
            }
            else {
                dp.push_back(dp[i - 1] + 2);
            }
            balance--;
            if (maxCount < dp[i]) {
                maxCount = dp[i];
            }
        }
        else {
            dp.push_back(0);
        }
    }

    return maxCount;
}
#pragma endregion

#pragma region 栈
int Solution32::longestValidParentheses2(std::string s) {
    int maxCount = 0;
    stack<int> stk;
    stk.push(-1);
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            stk.push(i);
        }
        else {
            stk.pop();
            if (stk.empty()) {
                stk.push(i);
            }
            else {
                maxCount = max(maxCount, i - stk.top());
            }
        }
    }
    return maxCount;
}
#pragma endregion

#pragma region 正逆遍历
int Solution32::longestValidParentheses3(string s) {
    int left = 0, right = 0, maxlength = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            left++;
        }
        else {
            right++;
        }
        if (left == right) {
            maxlength = max(maxlength, 2 * right);
        }
        else if (right > left) {
            left = right = 0;
        }
    }
    left = right = 0;
    for (int i = (int)s.length() - 1; i >= 0; i--) {
        if (s[i] == '(') {
            left++;
        }
        else {
            right++;
        }
        if (left == right) {
            maxlength = max(maxlength, 2 * left);
        }
        else if (left > right) {
            left = right = 0;
        }
    }
    return maxlength;
}
#pragma endregion



