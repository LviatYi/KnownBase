#include "Solutions.h"

#include <iostream>
#include <vector>

int hj6() {
    int input;
    auto primeList = std::vector<int>({2});
    while (std::cin >> input) {
        auto factor = 2;
        while (input > 1 && factor <= sqrt(input)) {
            if (input % factor == 0) {
                input /= factor;
                std::cout << factor << ' ';
            } else {
                ++factor;
            }
        }
        if (input > 1) std::cout << input << ' ';
    }

    return 0;
}
