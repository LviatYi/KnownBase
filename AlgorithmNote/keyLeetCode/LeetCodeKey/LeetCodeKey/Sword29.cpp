#include "Sword29.h"

static std::pair<int, int> offsets[4] = {
    {0,1},
    {1,0},
    {0,-1},
    {-1,0}
};

vector<int> Sword29::spiralOrder(vector<vector<int>>& matrix) {
    vector<int> ans;

    if (matrix.size() == 0 || matrix[0].size() == 0) {
        return ans;
    }
    int i = 0, j = 0;
    int xStart = -1, yStart = -1;
    int yEnd = matrix.size(), xEnd = matrix[0].size();
    int k = 0;
    std::pair<int, int> offset = offsets[0];

    while (xStart < xEnd && yStart < yEnd) {
        while (i > yStart && i <yEnd && j>xStart && j < xEnd) {
            ans.push_back(matrix[i][j]);
            i += offset.first;
            j += offset.second;
        }
        i -= offset.first;
        j -= offset.second;

        switch (k) {
        case 0:
            k++;
            yStart += 1;
            break;
        case 1:
            k++;
            xEnd -= 1;
            break;
        case 2:
            k++;
            yEnd -= 1;
            break;
        case 3:
            k = 0;
            xStart += 1;
            break;
        default:
            break;
        }

        offset = offsets[k];
        i += offset.first;
        j += offset.second;
    }

    return ans;
}
