#include "Sword4.h"

bool Sword4::findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
    int xEnd = matrix.size();
    if (!xEnd) {
        return false;
    }
    int yEnd = matrix[0].size();
    if (!yEnd) {
        return false;
    }

    for (int i = 0; i < xEnd; i++) {
        for (int j = 0; j < yEnd; j++) {
            if (matrix[i][j] < target) {
                continue;
            }
            else if (matrix[i][j] == target) {
                return true;
            }
            else {
                yEnd = j;
                break;
            }
        }
    }

    return false;
}

