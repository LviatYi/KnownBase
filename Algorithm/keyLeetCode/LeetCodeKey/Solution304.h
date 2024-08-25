#pragma once
#include <vector>

class Solution304 {
private:
    std::vector<std::vector<int>> content_;
public:
    Solution304(std::vector<std::vector<int>>& matrix);

    int sum_region(int row1, int col1, int row2, int col2);
};
