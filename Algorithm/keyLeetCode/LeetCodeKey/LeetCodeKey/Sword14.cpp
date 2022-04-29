#include "Sword14.h"
#include <math.h>
#include<iostream>

static int cuttingRopeMul(int n, int m) {
    long long a = pow(floor((double)n / m), m - 1) * (n - floor((double)n / m) * (m - 1));
    long long b = pow(ceil((double)n / m), m - 1) * (n - ceil((double)n / m) * (m - 1));
    return a > b ? a : b;
}

int Sword14::cuttingRope(int n) {
    int max = 0;
    for (int i = 2; i <= n; i++) {
        int t = cuttingRopeMul(n, i);
        if (t > max) {
            max = t;
        }

    }
    return max;
}

static long long quickPow(int x, int n) {
    long long res = 1;
    long long tt = x;
    while (n != 0) {
        if ((n & 1) == 1) {
            res *= tt;
            res %= 1000000007;
        }
        tt *= tt;
        tt %= 1000000007;
        n /= 2;
    }
    return res;
}

int Sword14::cuttingRope2(int n) {
    if (n <= 3) {
        return n - 1;
    }
    int a = n / 3;
    int b = n % 3;
    if (b == 2) {
        return (int)(quickPow(3, a) * b % 1000000007);
    }
    else {
        return (int)((quickPow(3, a - 1) * (b + 3)) % 1000000007);
    }
}