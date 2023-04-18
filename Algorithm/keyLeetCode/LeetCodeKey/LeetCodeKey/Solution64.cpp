#include "Solution64.h"

int Solution64::minPathSum(std::vector<std::vector<int>>& grid) {
    if (grid.empty()) {
        return -1;
    }

    int m = grid.size();
    int n = grid[0].size();

    std::vector dp_roll_sing = std::vector<int>(n);

    for (int i = m - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            if (i == m - 1 && j == n - 1) {
                dp_roll_sing[j] = grid[i][j];
            }
            else {
                dp_roll_sing[j] = std::min((i + 1 < m ? dp_roll_sing[j] : INT_MAX),
                                           (j + 1 < n ? dp_roll_sing[j + 1] : INT_MAX)) + grid[i][j];
            }
        }
    }

    return dp_roll_sing[0];
}
