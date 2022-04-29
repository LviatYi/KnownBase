#include "Sword46.h"

int Sword46::translateNum(int num) {
    if (num < 10) {
        return 1;
    }
    else if (num < 26) {
        return 2;
    }
    else if (num < 100) {
        return 1;
    }

    int front = num;
    int digit = 1;
    int sum = 0;

    while (front >= 100) {
        front /= 10;
        digit *= 10;
    }

    if (front < 26) {
        sum += translateNum(num % digit);
    }
    sum += translateNum(num % (digit * 10));

    return sum;
}
