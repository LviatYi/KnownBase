#include "Solutions.h"

#include <iostream>
#include <string>

int od2520() {
    int capacity;
    int task_count;
    std::cin >> capacity >> task_count;

    int curr_count;
    int last = 0;
    int p = task_count;
    while (p--) {
        std::cin >> curr_count;
        curr_count += last;
        curr_count -= capacity;
        last = std::max(curr_count, 0);
    }

    std::cout << task_count + std::ceil(float(last) / capacity);

    return 0;
}
