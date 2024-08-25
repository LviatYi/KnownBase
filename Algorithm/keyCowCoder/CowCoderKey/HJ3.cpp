#include "Solutions.h"

#include <iostream>

int hj3() {
    int count;
    while (std::cin >> count) {
        if (count <= 0) break;

        int t[500] = {};
        while (count--) {
            int input;
            std::cin >> input;
            ++t[input - 1];
        }

        for (size_t i = 0; i < std::size(t); ++i) {
            if (t[i] > 0) {
                std::cout << i + 1 << '\n';
            }
        }
    }

    return 0;
}
