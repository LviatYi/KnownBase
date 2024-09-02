#include "Solution554.h"

#include <map>

int Solution554::leastBricks(std::vector<std::vector<int>>& wall) {
    std::vector<std::vector<int>> wall_brick_steps(wall.size(), std::vector<int>());
    std::map<int, int> result_counter;
    for (int wall_row_index = 0; wall_row_index < wall.size(); ++wall_row_index) {
        auto const& wall_row = wall[wall_row_index];
        int step = 0;
        for (int wall_column_index = 0; wall_column_index < wall_row.size() - 1; ++wall_column_index) {
            auto const& brick_length = wall_row[wall_column_index];
            step += brick_length;
            wall_brick_steps[wall_row_index].push_back(step);

            if (result_counter.find(step) != result_counter.end()) {
                result_counter[step] += 1;
            } else {
                result_counter[step] = 1;
            }
        }
    }

    auto max_iter = std::max_element(result_counter.begin(),
                                     result_counter.end(),
                                     [](std::pair<int, int> const& a, std::pair<int, int> const& b) {
                                         return a.second < b.second;
                                     });
    return wall.size() - (*max_iter).second;
}
