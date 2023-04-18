#include "Solution120.h"

int Solution120::minimumTotal(std::vector<std::vector<int>>& triangle) {
    if (triangle.size() == 1) {
        return triangle[0][0];
    }

    std::vector<int> dp(triangle.size());
    dp[0] = triangle[0][0];

    int ans = INT_MAX;
    for (int i = 1; i < triangle.size(); ++i) {
        for (int j = i; j >= 0; --j) {
            dp[j] = std::min(j - 1 >= 0
                                 ? dp[j - 1]
                                 : INT_MAX,
                             j < i
                                 ? dp[j]
                                 : INT_MAX
                )
                + triangle[i][j];

            if (i == triangle.size() - 1) {
                ans = std::min(ans, dp[j]);
            }
        }
    }

    return ans;
}
