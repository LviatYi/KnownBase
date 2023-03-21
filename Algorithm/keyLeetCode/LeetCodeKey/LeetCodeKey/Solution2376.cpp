#include "Solution2376.h"

#include <functional>
#include <iostream>
#include <string>
#include <vector>

int Solution2376::countSpecialNumbers(int n) {
    std::string num_str = std::to_string(n);
    int length = num_str.size();
    int** cache = new int*[length];

    for (int i = 0; i < length; ++i) {
        cache[i] = new int[1 << 10]();
        for (int j = 0; j < 1 << 10; ++j) {
            cache[i][j] = -1;
        }
    }

    std::function<int(int, int, bool)> f = [&](int index, int mask, bool isLimit)-> int {
        if (index >= length) {
            return mask != 0;
        }
        if (!isLimit && cache[index][mask] != -1) {
            return cache[index][mask];
        }

        int ret = 0;

        const int limit = isLimit ? num_str[index] - '0' : 9;

        if (!(mask & 1)) {
            ret += mask != 0
                       ? f(index + 1, mask | 1, isLimit && 0 == limit)
                       : f(index + 1, mask, isLimit && 0 == limit);
        }

        for (int i = 1; i <= limit; ++i) {
            ret += !(mask & 1 << i) ? f(index + 1, mask | 1 << i, isLimit && i == limit) : 0;
        }

        if (!isLimit) {
            cache[index][mask] = ret;
        }
        return ret;
    };

    return f(0, 0, true);
}
