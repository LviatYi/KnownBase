#include "Sword15.h"
#include<limits>

int Sword15::hammingWeight(uint32_t n) {
    uint32_t i = 0x80000000;
    int count = 0;
    while (n > 0) {
        if (n & i) {
            count++;
            n -= i;
        }
        i >>= 1;
    }
    return count;
}
