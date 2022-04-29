#include "Solution50.h"

double Solution50::myPow(double x, int n) {
    bool isNeg = n < 0;
    double ans = 1;

    while (n != 0) {
        if (n % 2) {
            ans *= x;
            n > 0 ? n-- : n++;
        }
        x *= x;
        n /= 2;
    }

    if (isNeg) {
        ans = 1 / ans;
    }
    return ans;
}
