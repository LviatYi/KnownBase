#include "Swordii95.h"

#include <vector>

int Swordii95::longestCommonSubsequence(std::string text1, std::string text2) {
    int m = text1.length(), n = text2.length();
    std::vector dp(m + 1, std::vector<int>(n + 1));
    for (int i = 1; i <= m; i++) {
        char c1 = text1.at(i - 1);
        for (int j = 1; j <= n; j++) {
            char c2 = text2.at(j - 1);
            if (c1 == c2) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[m][n];
}
