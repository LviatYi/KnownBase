#include "Solutions.h"

#include <iostream>
#include <string>

int hj2() {
    std::string input;
    char tag;

    while (getline(std::cin, input)) {
        tag = '\0';
        std::cin >> tag;
        if (tag == '\0') {
            return 0;
        }
        if (std::isupper(tag)) {
            tag = static_cast<char>(std::tolower(tag));
        }
        int count = 0;
        for (char c : input) {
            if (tag == std::tolower(c)) {
                ++count;
            }
        }
        printf("%d", count);
    }

    return 0;
}
