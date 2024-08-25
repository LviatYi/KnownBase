#include "Sword43.h"
#include<vector>

using std::vector;

int Sword43::countDigitOne(int n) {
    long i = 1;
    int t = n;
    int sum = 0;

    while (t > 0) {
        sum += t / 10 * i;
        if (t % 10 == 1) {
            sum += n % i + 1;
        }
        else if (t % 10 > 1) {
            sum += i;
        }

        i *= 10;
        t /= 10;
    }

    return sum;
}