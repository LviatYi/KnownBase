#include "Solutions.h"

#include <iostream>
#include <map>

int hj9() {
    std::string str;

    while (std::cin >> str) {
        int record[10] = {};
        for (int i = str.size() - 1; i >= 0; --i) {
            if (record[str[i] - '0'] <= 0) {
                std::cout << str[i];
                ++record[str[i] - '0'];
            }
        }
    }

    return 0;
}
