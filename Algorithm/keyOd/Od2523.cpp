#include "Solutions.h"

#include <iostream>
#include <queue>
#include <string>

int od2523() {
    int capacity;
    std::cin >> capacity;
    std::priority_queue<int> weights;

    while (capacity--) {
        int w;
        std::cin >> w;
        weights.push(w);
    }

    while (weights.size() >= 3) {
        int m, n, o;
        m = weights.top();
        weights.pop();
        n = weights.top();
        weights.pop();
        o = weights.top();
        weights.pop();

        int last = std::abs(m - 2 * n + o);
        if (last > 0) {
            weights.push(last);
        }
    }

    std::cout << weights.top() << std::endl;
    return 0;
}
