#include "Solution1094.h"

#include <array>

bool Solution1094::carPooling(std::vector<std::vector<int>>& trips, int capacity) {
    std::array<int, 1001> diff_info;
    diff_info.fill(0);

    for (int i = 0; i < trips.size(); ++i) {
        const auto& trip = trips[i];
        diff_info[trip[1]] += trip[0];
        diff_info[trip[2]] -= trip[0];
    }

    int max = 0;
    int sum = 0;
    for (int i = 0; i < diff_info.size(); ++i) {
        sum += diff_info[i];
        if (sum > max) {
            max = sum;
        }
    }

    return capacity >= max;
}
