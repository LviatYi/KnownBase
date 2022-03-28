#include "Sword10.h"
using namespace std;

int dp1[101] = { 0,1 };

int Sword10::fib(int n) {
    if (n > 1) {
        if (!dp1[n]) {
            dp1[n] = fib(n - 1) + fib(n - 2);
            dp1[n] %= 1000000007;
        }
    }

    return dp1[n];
}

int dp2[101] = { 1,1,2 };

int Sword10::numWays(int n) {
    if (n > 2) {
        if (!dp2[n]) {
            dp2[n] = numWays(n - 1) + numWays(n - 2);
            dp2[n] %= 1000000007;
        }
    }

    return dp2[n];
}
