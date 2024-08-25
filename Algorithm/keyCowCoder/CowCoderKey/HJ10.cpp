#include "Solutions.h"

#include <iostream>

constexpr int size = 256;

int hj10() {
    int record[size] = {0};
    std::string str;
    while (std::cin >> str) {
        for (const char c : str) {
            ++record[c];
        }

        auto sum = 0;
        for (const auto r : record) {
            if (r > 0) { ++sum; }
        }

        std::cout << sum << std::endl;
    }

    return 0;
}
