#include "Solutions.h"
#include <iostream>
#include <string>

constexpr int size = 256;

int hj11() {
    std::string str;
    std::getline(std::cin, str);
    copy(str.rbegin(),
         str.rend(),
         std::ostreambuf_iterator<char>(std::cout));

    return 0;
}
