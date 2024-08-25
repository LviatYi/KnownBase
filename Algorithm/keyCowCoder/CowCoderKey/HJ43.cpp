#include <iostream>
#include <vector>

const std::vector<std::pair<int, int>> directions = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
};

int hj43_dfs(std::vector<std::vector<bool>>& map,
             std::vector<std::pair<size_t, size_t>>& path,
             size_t x,
             size_t y) {
    if (x == map.size() - 1 && y == map[0].size() - 1) {
        path.emplace(path.end(), x, y);
        return 1;
    }

    int min = INT_MAX;
    for (const auto [dx, dy] : directions) {
        if (int(x) + dx < 0 ||
            x + dx >= map.size() ||
            int(y) + dy < 0 ||
            y + dy >= map[0].size()) {
            continue;
        }
        if (map[x + dx][y + dy]) {
            continue;
        }
        std::vector<std::pair<size_t, size_t>> path_record;

        int cur_x = x + dx;
        int cur_y = y + dy;
        map[cur_x][cur_y] = true;
        int length = hj43_dfs(map,
                              path_record,
                              cur_x,
                              cur_y);
        map[cur_x][cur_y] = false;

        if (length != -1 && length < min) {
            min = length;
            path = path_record;
        }
    }

    if (min == INT_MAX) return -1;

    path.emplace_back(x, y);
    return min;
}

int hj43() {
    int a, b;
    while (std::cin >> a >> b) {
        std::vector map(a, std::vector<bool>(b));
        std::vector<std::pair<size_t, size_t>> path;

        for (int i = 0; i < a; ++i) {
            for (int j = 0; j < b; ++j) {
                bool val;
                std::cin >> val;
                map[i][j] = val;
            }
        }

        map[0][0] = true;
        hj43_dfs(map, path, 0, 0);

        for (int i = path.size() - 1; i >= 0; --i) {
            std::cout
                << "("
                << path[i].first
                << ","
                << path[i].second
                << ")"
                << std::endl;
        }
    }

    return 0;
}
