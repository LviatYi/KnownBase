#include "Solution256.h"

int Solution256::minCost(std::vector<std::vector<int>>& costs) {
    size_t n = costs.size();
    size_t size = costs[0].size();
    std::vector<int> dp_last = std::vector<int>(size);
    std::vector<int> dp = std::vector<int>(size);

    for (int i = 0; i < size; ++i) {
        dp[i] = costs[0][i];
    }

    for (int i = 1; i < n; ++i) {
        std::swap(dp_last, dp);
        for (int j = 0; j < size; ++j) {
            int min = INT_MAX;
            for (int k = 0; k < size; ++k) {
                if (k == j) {
                    continue;
                }
                min = std::min(min, dp_last[k]);
            }
            dp[j] = min + costs[i][j];
        }
    }

    int min = INT_MAX;
    for (int i = 0; i < size; ++i) {
        min = std::min(min, dp[i]);
    }

    return min;
}
