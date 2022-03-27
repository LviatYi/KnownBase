#include "Sword4.h"

bool Sword4::findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
    if (!matrix.size()) {
        return false;
    }
    int i = 0;
    int j = matrix[0].size() - 1;
    if (!j) {
        return false;
    }

    while (i < matrix.size() && j>=0) {
        if (matrix[i][j] > target) {
            j--;
        }
        else if (matrix[i][j] == target) {
            return true;
        }
        else {
            i++;
        }
    }

    return false;
}

