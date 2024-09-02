#include <iostream>
#include <vector>
using namespace std;

void dfs(std::vector<std::vector<bool>>& visited,
         std::vector<std::vector<int>>& map,
         int i,
         int j,
         int from_height,
         int& current_count) {
    if (i < 0
        || j < 0
        || i >= visited.size()
        || j >= visited[0].size())
        return;
    if (visited[i][j])return;

    if (std::abs(map[i][j] - from_height) <= 1) {
        ++current_count;
        visited[i][j] = true;
        dfs(visited, map, i - 1, j, map[i][j], current_count);
        dfs(visited, map, i + 1, j, map[i][j], current_count);
        dfs(visited, map, i, j - 1, map[i][j], current_count);
        dfs(visited, map, i, j + 1, map[i][j], current_count);
    }
}

int odRun3() {
    int row, col;
    std::cin >> row >> col;
    auto map = std::vector<std::vector<int>>(row, std::vector<int>(col));

    for (int r = 0; r < row; ++r) {
        for (int c = 0; c < col; ++c) {
            std::cin >> map[r][c];
        }
    }

    auto visited = std::vector<std::vector<bool>>(row, std::vector<bool>(col));

    int max = 0;
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[0].size(); ++j) {
            int sum = 0;
            if (visited[i][j]) {
                continue;
            }

            dfs(visited, map, i, j, map[i][j], sum);
            if (sum > max) {
                max = sum;
            }
        }
    }


    std::cout << max << std::endl;

    return 0;
}
