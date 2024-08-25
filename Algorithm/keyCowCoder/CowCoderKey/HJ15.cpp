#include "Solutions.h"
#include <iostream>

int hj15() {
    int input;

    while (std::cin >> input) {
        auto p = 1;
        auto hamming_weight = 0;
        while (p <= input) {
            if (input & p) {
                ++hamming_weight;
            }
            p <<= 1;
        }

        std::cout << hamming_weight << std::endl;
    }

    return 0;
}
