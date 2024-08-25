#include "Solutions.h"
#include <iostream>
#include <queue>
#include <string>
#include <vector>

int hj14() {
    int count;

    while (std::cin >> count) {
        auto queue = std::priority_queue<std::string, std::vector<std::string>, std::greater<>>();
        for (int i = 0; i < count; ++i) {
            std::string str;
            std::cin >> str;

            queue.push(str);
        }
        while (!queue.empty()) {
            std::cout << queue.top() << std::endl;
            queue.pop();
        }
    }

    return 0;
}
