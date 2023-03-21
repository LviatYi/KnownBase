#include "Solution2373.h"

#include <queue>

std::vector<std::vector<int>> Solution2373::largestLocal(std::vector<std::vector<int>>& grid) {
    if (grid.size() < 3 || grid[0].size() < 3) {
        return {};
    }

    int length = grid.size();

    std::vector<std::vector<int>> ret(length - 2);

    for (int i = 0; i < length - 2; ++i) {
        ret[i] = std::vector<int>(length - 2);
    }

    for (int i = 0; i < length - 2; ++i) {
        for (int j = 0; j < length - 2; ++j) {
            int max = 0;
            for (int p = 0; p < 3; ++p) {
                for (int q = 0; q < 3; ++q) {
                    max = std::max(max, grid[i + p][j + q]);
                }
            }

            ret[i][j] = max;
        }
    }

    return ret;
}
