#include "Solution1605.h"

std::vector<std::vector<int>> Solution1605::restoreMatrix(std::vector<int>& rowSum, std::vector<int>& colSum) {
    auto ret = std::vector<std::vector<int>>(rowSum.size());

    for (int i = 0; i < rowSum.size(); ++i) {
        ret[i] = std::vector<int>(colSum.size());
    }

    for (int i = 0; i < rowSum.size(); ++i) {
        int energy = rowSum[i];
        for (int j = 0; j < colSum.size(); ++j) {
            int take = std::min(energy, colSum[j]);
            colSum[j] -= take;
            energy -= take;
            ret[i][j] = take;
            if (energy == 0) {
                break;
            }
        }
    }

    return ret;
}
