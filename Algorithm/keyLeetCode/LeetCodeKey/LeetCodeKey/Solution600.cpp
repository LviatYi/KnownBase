#include "Solution600.h"

int Solution600::findIntegers(int n) {
    int benchmark = 1;
    int i = 2;

    while (benchmark < n) {
        dp_[i] = dp_[i - 1] + dp_[i - 2];
        ++i;
        benchmark <<= 1;
    }


    bool pre = false;
    int ret = 0;
    for (int j = 29; j >= 0; --j) {
        if ((1 << j & n) != 0) {
            ret += dp_[j + 1];

            if (pre) {
                break;
            }
            pre = true;
        }
        else {
            pre = false;
        }

        if (j == 0) {
            ++ret;
        }
    }

    return ret;
}
