#pragma once
#include <vector>

class Swordii13 {
private:
    std::vector<std::vector<int>> content_;
public:
    Swordii13(std::vector<std::vector<int>>& matrix);

    int sum_region(int row1, int col1, int row2, int col2);
};
