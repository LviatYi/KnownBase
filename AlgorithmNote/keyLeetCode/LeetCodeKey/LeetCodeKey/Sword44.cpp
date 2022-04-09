#include "Sword44.h"
#include<string>

using std::string;
using std::to_string;
using std::stoi;

int Sword44::findNthDigit(int n) {
    if (n < 10) {
        return n;
    }

    int t = n - 9;
    int phase = 10;
    int bitCount = 2;

    while (t / phase > 9 * bitCount) {
        t -= 9 * phase * bitCount;
        phase *= 10;
        bitCount++;
    }

    int num = (t - 1) / bitCount + phase;
    string s = to_string(num);

    return s[(t - 1) % bitCount] - '0';
}
