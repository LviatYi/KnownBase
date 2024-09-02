#include <iostream>
#include <queue>
#include <set>
#include <vector>

class PairFistCmp {
public:
    bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
        return lhs.second > rhs.second;
    }
};

int od4610() {
    int count;
    int relation_count;
    std::cin >> count >> relation_count;
    auto path = std::vector<std::vector<int>>(count, std::vector<int>(count, -1));
    for (int cin_i = 0; cin_i < relation_count; ++cin_i) {
        int f, t, c;
        std::cin >> f >> t >> c;
        path[f - 1][t - 1] = c;
    }
    int start_at;
    std::cin >> start_at;
    --start_at;

    auto visited = std::vector<int>(count, -1);
    auto finished_set = std::set<int>();
    visited[start_at] = 0;
    auto q = std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, PairFistCmp>();
    q.push({start_at, 0});

    while (!q.empty() && finished_set.size() < count) {
        const auto focus = q.top();
        finished_set.insert(focus.first);
        q.pop();

        for (int curr_path_index = 0;
             curr_path_index < path[focus.first].size();
             ++curr_path_index) {
            const auto next_cost = path[focus.first][curr_path_index];
            const auto curr_cost = focus.second;
            if (next_cost > -1) {
                if (visited[curr_path_index] == -1
                    || curr_cost + next_cost < visited[curr_path_index]) {
                    visited[curr_path_index] = curr_cost + next_cost;
                    q.push(std::make_pair(curr_path_index, curr_cost + next_cost));
                }
            }
        }
    }

    int max = 0;
    for (auto is_visited : visited) {
        if (is_visited == -1) {
            std::cout << -1 << std::endl;
            return 0;
        }

        if (is_visited > max) {
            max = is_visited;
        }
    }

    std::cout << max << std::endl;

    return 0;
}
