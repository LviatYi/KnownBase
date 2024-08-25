#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int hj34() {
    std::vector<char> input;
    char c;
    while (std::cin >> c) {
        input.push_back(c);
    }

    std::sort(input.begin(), input.end());

    for (const auto c : input) {
        std::cout << c;
    }

    return 0;
}
