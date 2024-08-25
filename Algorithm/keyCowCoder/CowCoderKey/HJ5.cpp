#include "Solutions.h"

#include <iostream>
#include <string>

int hj5() {
    std::string input;
    while (std::getline(std::cin, input)) {
        auto factor = 1;
        auto sum = 0;
        for (int i = input.size() - 1; i >= 0; --i) {
            if (std::isxdigit(input[i])) {
                if (std::isdigit(input[i])) {
                    sum += (input[i] - '0') * factor;
                } else {
                    sum += (std::toupper(input[i]) - 'A' + 10) * factor;
                }
                factor *= 16;
            } else {
                break;
            }
        }

        std::cout << sum << '\n';
    }

    return 0;
}
