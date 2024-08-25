#pragma once
#include <vector>

class Solution200 {
private:
    void dye(std::vector<std::vector<bool>>& visited, std::vector<std::vector<char>>& grid, int i, int j);

public:
    int numIslands(std::vector<std::vector<char>>& grid);
};
