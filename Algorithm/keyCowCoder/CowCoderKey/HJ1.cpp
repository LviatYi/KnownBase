#include "Solutions.h"

#include <iostream>
#include <string>

int hj1() {
    std::string input;

    while (getline(std::cin, input)) {
        size_t p = input.find_last_of(' ');
        printf("%zu",
               p == std::string::npos
                   ? input.size()
                   : input.size() - p - 1);
    }
    return 0;
}
