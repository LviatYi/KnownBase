#include "Swordii13.h"

Swordii13::Swordii13(std::vector<std::vector<int>>& matrix) {
    content_ = std::vector<std::vector<int>>();

    for (int i = 0; i < matrix.size(); ++i) {
        auto content_vector = std::vector<int>();
        for (int j = 0; j < matrix[i].size(); ++j) {
            content_vector.push_back(
                matrix[i][j] +
                (j > 0
                     ? content_vector.back()
                     : 0)
                +
                (i > 0
                     ? content_[i - 1][j]
                     : 0)
                - (i > 0 && j > 0
                       ? content_[i - 1][j - 1]
                       : 0));
        }
        content_.push_back(content_vector);
    }

    return;
}

int Swordii13::sum_region(int row1, int col1, int row2, int col2) {
    return
        content_[row2][col2]
        + (row1 > 0 && col1 > 0 ? content_[row1 - 1][col1 - 1] : 0)
        - (col1 > 0 ? content_[row2][col1 - 1] : 0)
        - (row1 > 0 ? content_[row1 - 1][col2] : 0);
}
