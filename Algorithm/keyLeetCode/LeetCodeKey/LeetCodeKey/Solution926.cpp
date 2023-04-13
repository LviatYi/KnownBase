#include "Solution926.h"

#include <vector>

int Solution926::minFlipsMonoIncr(std::string s) {
    size_t n = s.size();
    std::vector<int> zero_count = std::vector<int>(n);
    for (int i = 0; i < n; ++i) {
        if (s[i] == '0') {
            zero_count[i] = (i > 0 ? zero_count[i - 1] : 0) + 1;
        }
        else {
            zero_count[i] = (i > 0 ? zero_count[i - 1] : 0);
        }
    }

    int min = zero_count[n - 1];
    for (int i = 0; i < zero_count.size(); ++i) {
        min = std::min(i + 1 - 2 * zero_count[i] + zero_count[n - 1], min);
    }

    return min;
}

#pragma region 动态规划

int Solution926::minFlipsMonoIncr2(std::string s) {
    int dp0 = 0, dp1 = 0;
    for (char c : s) {
        int dp0New = dp0, dp1New = std::min(dp0, dp1);
        if (c == '1') {
            dp0New++;
        }
        else {
            dp1New++;
        }
        dp0 = dp0New;
        dp1 = dp1New;
    }
    return std::min(dp0, dp1);
}

#pragma endregion
