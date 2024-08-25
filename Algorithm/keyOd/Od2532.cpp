#include "Solutions.h"

#include <iostream>
#include <string>
#include <climits>

int od2532() {
    std::string input;
    std::cin >> input;

    size_t last = 0;
    unsigned int count = 0;
    const int UNDEFINE_HEIGHT = INT_MIN;
    int last_val_1 = UNDEFINE_HEIGHT;
    int last_val_2 = UNDEFINE_HEIGHT;

    while (last < input.size()) {
        size_t p = input.find(',', last);
        if (p == std::string::npos) {
            p = input.size();
        }
        int val = std::stoi(input.substr(last, p));

        if (last_val_2 == UNDEFINE_HEIGHT) {
        } else if (last_val_1 == UNDEFINE_HEIGHT) {
            if (last_val_2 > val) {
                ++count;
            }
        } else if (last_val_2 > last_val_1 && last_val_2 > val) {
            ++count;
        }

        last_val_1 = last_val_2;
        last_val_2 = val;

        last = p + 1;
    }

    if (last_val_1 == UNDEFINE_HEIGHT
            ? last_val_2 != 0
            : last_val_1 < last_val_2) {
        ++count;
    }

    std::cout << count << std::endl;
    return 0;
}
