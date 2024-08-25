#include "Solution5.h"
#include <vector>

using namespace std;

string Solution5::longestPalindrome(string s) {
    // 动态规划法

    // 记录指定首尾位置的子串是否为回文字符串
    vector<vector<int>> isPalindromeString = vector<vector<int>>(s.length(), vector<int>(s.length(), -1));
    int maxLength = 1;
    int begin = 0;

    if (s.length() < 2) {
        return s;
    }
    for (int i = 0; i < s.length(); i++) {
        isPalindromeString[i][i] = 1;
    }

    // 枚举待判断子串长度
    for (int l = 2; l <= s.length(); l++) {
        // 枚举起始位置
        for (int i = 0; i < s.length(); i++) {
            if (l == 2) {
                if (s[i] == s[i + 1]) {
                    isPalindromeString[i][i + 1] = 2;
                }
            }
            // 计算结束位置
            int j = i + l - 1;
            if (j >= s.length()) {
                break;
            }
            else if (isPalindromeString[i + 1][j - 1] != -1 && s[i] == s[j]) {
                isPalindromeString[i][j] = isPalindromeString[i + 1][j - 1] + 2;
            }
            if (maxLength < isPalindromeString[i][j]) {
                maxLength = isPalindromeString[i][j];
                begin = i;
            }
        }
    }
    return s.substr(begin, maxLength);
}

string Solution5::longestPalindrome2(string s) {
    // 中心扩张算法

    int maxLength = 1;
    int begin = 0;
    for (int i = 0; i < s.length(); i++) {
        int count = 1;
        int start, end;
        start = end = i;

        // 中心同字符扩张
        while (true) {
            if (start - 1 >= 0 && s[start - 1] == s[i]) {
                start--;
                count++;
            }
            else if (end + 1 <= s.length() && s[end + 1] == s[i]) {
                end++;
                count++;
            }
            else {
                break;
            }
        }

        // 首尾相同字母则扩张
        while (--start >= 0 && ++end < s.length() && s[start] == s[end]) {
            count += 2;
        }

        if (maxLength < count) {
            maxLength = count;
            begin = start + 1;
        }
    }
    return s.substr(begin, maxLength);
}


