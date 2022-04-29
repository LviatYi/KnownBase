#include "Solution7.h"
#include <limits>

int Solution7::reverse(int x) {
    long n = 0;
    while (x) {
        n = n * 10 + x % 10;
        x /= 10;
    }
    return n > INT_MAX || n < INT_MIN ? 0 : n;
}
