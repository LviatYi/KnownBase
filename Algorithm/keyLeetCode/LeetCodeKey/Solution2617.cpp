﻿#include "Solution2617.h"

#include <queue>

int Solution2617::minimumVisitedCells(std::vector<std::vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    std::vector<std::vector<int>> dist(m, std::vector<int>(n, -1));
    using pii = std::pair<int, int>;
    std::vector<std::priority_queue<pii, std::vector<pii>, std::greater<pii>>> row(m);
    std::vector<std::priority_queue<pii, std::vector<pii>, std::greater<pii>>> col(n);
    dist[0][0] = 1;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            while (!row[i].empty() && grid[i][row[i].top().second] + row[i].top().second < j) {
                row[i].pop();
            }
            if (!row[i].empty() && (dist[i][j] == -1 || row[i].top().first + 1 < dist[i][j])) {
                dist[i][j] = row[i].top().first + 1;
            }
            while (!col[j].empty() && grid[col[j].top().second][j] + col[j].top().second < i) {
                col[j].pop();
            }
            if (!col[j].empty() && (dist[i][j] == -1 || col[j].top().first + 1 < dist[i][j])) {
                dist[i][j] = col[j].top().first + 1;
            }
            if (dist[i][j] != -1) {
                row[i].emplace(dist[i][j], j);
                col[j].emplace(dist[i][j], i);
            }
        }
    }
    return dist[m - 1][n - 1];
}
