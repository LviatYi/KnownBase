#include "Solution6.h"

#include <string>

string Solution6::convert(string s, int numRows) {
    if (numRows == 1) {
        return s;
    }

    int t = numRows * 2 - 2;
    string ans;

    for (int i = 0; i * t < s.length(); i++) {
        ans.push_back(s[i * t]);
    }

    for (int j = 1; j < numRows - 1; j++) {
        for (int i = 0; i < s.length() / t + 1; i++) {
            if (i * t + j < s.length()) {
                ans.push_back(s[i * t + j]);
            }
            if ((i + 1) * t - j < s.length()) {
                ans.push_back(s[(i + 1) * t - j]);
            }
        }
    }

    for (int i = 0; i * t + numRows - 1 < s.length(); i++) {
        ans.push_back(s[i * t + numRows - 1]);
    }

    return ans;
}
