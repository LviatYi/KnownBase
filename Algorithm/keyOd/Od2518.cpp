#include "Solutions.h"

#include <iostream>
#include <string>

void output_od2518(int count, char* stack, int count_upper, int count_lower) {
    stack[count] = '\0';
    if (count_upper > count_lower) {
        for (int i = 0; i < count; ++i) {
            stack[i] = std::toupper(stack[i]);
        }
    } else if (count_upper < count_lower) {
        for (int i = 0; i < count; ++i) {
            stack[i] = std::tolower(stack[i]);
        }
    }
    std::cout << '-' << std::string(stack);
}

int od2518() {
    int size;
    std::cin >> size;
    char c;
    bool first_word = false;
    const auto stack = new char[size + 1];
    int count = 0;
    int count_upper = 0;
    int count_lower = 0;
    while (std::cin >> c) {
        if (!first_word) {
            if (c == '-') first_word = true;
            else std::cout << c;
        } else if (c == '-') {
        } else {
            stack[count] = c;
            ++count;
            if (std::isupper(c)) {
                ++count_upper;
            } else if (std::islower(c)) {
                ++count_lower;
            }
        }

        if (count == size) {
            output_od2518(count, stack, count_upper, count_lower);
            count = 0;
            count_upper = 0;
            count_lower = 0;
        }
    }

    if (count > 0) {
        output_od2518(count, stack, count_upper, count_lower);
    }

    delete[] stack;
    return 0;
}
