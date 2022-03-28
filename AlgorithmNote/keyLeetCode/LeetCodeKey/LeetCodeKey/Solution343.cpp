#include "Solution343.h"
#include<vector>
#include<math.h>

using std::vector;
using std::max;

int Solution343::integerBreak(int n) {
    vector <int> dp(n + 1);
    for (int i = 2; i <= n; i++) {
        int curMax = 0;
        for (int j = 1; j < i; j++) {
            curMax = max(curMax, max(j * (i - j), j * dp[i - j]));
        }
        dp[i] = curMax;
    }
    return dp[n];
}