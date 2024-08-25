#include "Solution97.h"

#include <vector>

bool Solution97::isInterleave(std::string s1, std::string s2, std::string s3) {
    int m = s1.length(), n = s2.length();
    if (m + n != s3.size()) {
        return false;
    }
    std::vector dp(m + 1, std::vector<bool>(n + 1));

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0 && j == 0) {
                dp[i][j] = true;
            }
            else {
                dp[i][j] = (j - 1 >= 0 && dp[i][j - 1] && s3[i + j - 1] == s2[j - 1])
                    || (i - 1 >= 0 && dp[i - 1][j] && s3[i + j - 1] == s1[i - 1]);
            }
        }
    }

    return dp[m][n];
}
