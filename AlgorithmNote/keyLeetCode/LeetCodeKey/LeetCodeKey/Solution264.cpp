#include "Solution264.h"
#include <vector>
#include <algorithm>

using std::vector;
using std::min;

int Solution264::nthUglyNumber(int n) {
    vector<int> uglyNums = { 1 };

    int p2 = 0;
    int p3 = 0;
    int p5 = 0;

    for (int i = 1; i < n; i++) {
        uglyNums.push_back(min<int>({ uglyNums.at(p2) * 2, uglyNums.at(p3) * 3, uglyNums.at(p5) * 5 }));
        if (uglyNums.at(i) == uglyNums.at(p2) * 2) {
            p2++;
        }
        if (uglyNums.at(i) == uglyNums.at(p3) * 3) {
            p3++;
        }
        if (uglyNums.at(i) == uglyNums.at(p5) * 5) {
            p5++;
        }
    }

    return uglyNums.at(n - 1);
}