#include "Solution62.h"

#include <vector>

int Solution62::uniquePaths(int m, int n) {
    if (m < n) {
        std::swap(m, n);
    }
    std::vector dp_roll_sing = std::vector<int>(n);

    for (int i = m - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            if (i == m - 1 && j == n - 1) {
                dp_roll_sing[j] = 1;
            }
            else {
                dp_roll_sing[j] = (i + 1 < m ? dp_roll_sing[j] : 0) + (j + 1 < n ? dp_roll_sing[j + 1] : 0);
            }
        }
    }

    return dp_roll_sing[0];
}
