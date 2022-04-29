#include "Solution9.h"

bool Solution9::isPalindrome(int x) {
    if (x == 0) {
        return true;
    }
    else if (x < 0 || x % 10 == 0) {
        return false;
    }

    int t = 0;
    while (x > t) {
        t = t * 10 + x % 10;
        x /= 10;
    }

    return t == x || t / 10 == x;
}
