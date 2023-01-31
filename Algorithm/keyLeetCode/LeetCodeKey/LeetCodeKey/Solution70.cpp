#include "Solution70.h"

int Solution70::climbStairs(int n) {
    if (n > 2) {
        if (!dp2[n]) {
            dp2[n] = climbStairs(n - 1) + climbStairs(n - 2);
            dp2[n] %= 1000000007;
        }
    }
    return dp2[n];
}
