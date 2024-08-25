#include "Solution200.h"

#include <vector>
#include <unordered_map>

using namespace std;

int Solution200::numIslands(std::vector<std::vector<char>>& grid) {
    std::vector visited(grid.size(), std::vector(grid[0].size(), false));

    int count = 0;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (visited[i][j])continue;

            if (grid[i][j] == '0') {
                visited[i][j] = true;
                continue;
            }

            ++count;
            dye(visited, grid, i, j);
        }
    }

    return count;
}

void Solution200::dye(std::vector<std::vector<bool>>& visited,
                      std::vector<std::vector<char>>& grid,
                      int i,
                      int j) {
    if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size()) return;
    if (visited[i][j]) return;
    if (grid[i][j] == '0') {
        visited[i][j] = true;
        return;
    }

    visited[i][j] = true;

    dye(visited, grid, i - 1, j);
    dye(visited, grid, i + 1, j);
    dye(visited, grid, i, j - 1);
    dye(visited, grid, i, j + 1);
}
