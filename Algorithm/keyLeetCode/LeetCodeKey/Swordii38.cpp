#include "Swordii38.h"

#include <stack>

std::vector<int> Swordii38::dailyTemperatures(std::vector<int>& temperatures) {
    if (temperatures.empty()) {
        return {};
    }

    std::stack<std::pair<int, int>> stack = {};
    std::vector<int> ret = std::vector<int>(temperatures.size(), 0);
    for (int i = temperatures.size() - 1; i >= 0; --i) {
        while (!stack.empty() && stack.top().first <= temperatures[i]) {
            stack.pop();
        }

        if (stack.empty()) {
            stack.push({temperatures[i], i});
        }
        else {
            ret[i] = stack.top().second - i;
            stack.push({temperatures[i], i});
        }

    }

    return ret;
}
