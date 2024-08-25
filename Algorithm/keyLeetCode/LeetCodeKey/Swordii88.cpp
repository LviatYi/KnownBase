#include "Swordii88.h"

int Swordii88::minCostClimbingStairs(std::vector<int>& cost) {
    std::vector<int> dp(cost.size() + 1);
    size_t n = cost.size();

    dp[0] = cost[0];
    dp[1] = cost[1];

    for (int i = 2; i <= n; ++i) {
        dp[i] = (i < cost.size() ? cost[i] : 0) + std::min(dp[i - 1], dp[i - 2]);
    }

    return dp[n];
}
