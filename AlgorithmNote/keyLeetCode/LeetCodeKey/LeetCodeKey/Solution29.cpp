#include "Solution29.h"
#include <math.h>
int Solution29::divide(int dividend, int divisor) {
    int flag = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
    long long _dividend = dividend > 0 ? long long(dividend) : long long(-dividend);
    long long _divisor = divisor > 0 ? long long(divisor) : long long(-divisor);

    int ans = 0;
    while (_dividend > _divisor) {
        _dividend -= _divisor;
        ans++;
    }
    return ans * flag;
}
