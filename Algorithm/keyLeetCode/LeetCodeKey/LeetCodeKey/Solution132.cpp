#include "Solution132.h"

#include <unordered_map>
#include <vector>

int Solution132::minCut(std::string s) {
    int n = s.size();
    std::vector<int> dp = std::vector<int>(n);
    for (int i = 0; i < n; ++i) {
        dp[i] = i + 1;
    }

    for (int i = 0; i < n; ++i) {
        dp[i] = std::min(dp[i], (i - 1 >= 0 ? dp[i - 1] : 0) + 1);
        for (int j = 1; i - j >= 0 && i + j < n; ++j) {
            if (s[i - j] == s[i + j]) {
                dp[i + j] = std::min(dp[i + j], (i - j - 1 >= 0 ? dp[i - j - 1] : 0) + 1);
            }
            else {
                break;
            }
        }

        if (i - 1 >= 0 && s[i - 1] == s[i]) {
            dp[i] = std::min(dp[i], (i - 2 >= 0 ? dp[i - 2] : 0) + 1);
            for (int j = 1; i - 1 - j >= 0 && i + j < n; ++j) {
                if (s[i - 1 - j] == s[i + j]) {
                    dp[i + j] = std::min(dp[i + j], (i - j - 2 >= 0 ? dp[i - j - 2] : 0) + 1);
                }
                else {
                    break;
                }
            }
        }
    }

    return dp[n - 1] - 1;
}
