#include <algorithm>

#include "Solutions.h"

#include <iostream>
#include <string>

int hj4() {
    std::string input;
    constexpr auto step = 8;
    while (std::getline(std::cin, input)) {
        if (input.empty()) break;

        auto p = 0;

        while (p < input.length()) {
            auto str = input.substr(p, step);
            if (str.length() < step) {
                str += std::string(step - str.length(), '0');
            }

            std::cout << str << std::endl;
            p += step;
        }
    }

    return 0;
}
