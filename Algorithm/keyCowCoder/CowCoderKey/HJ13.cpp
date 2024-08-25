#include "Solutions.h"
#include <iostream>
#include <string>
#include <vector>

int hj13() {
    auto record = std::vector<std::string>();
    std::string str;

    while (std::cin >> str) {
        record.push_back(str);
    }

    auto iter_r = record.rbegin();
    while (iter_r != record.rend()) {
        std::cout << *iter_r << " ";
        ++iter_r;
    }

    return 0;
}
