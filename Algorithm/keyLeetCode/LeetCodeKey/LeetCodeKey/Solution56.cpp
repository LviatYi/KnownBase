#include "Solution56.h"

#include <algorithm>

std::vector<std::vector<int>> Solution56::merge(std::vector<std::vector<int>>& intervals) {
    std::sort(intervals.begin(), intervals.end(),
              [](const std::vector<int>& lhs, const std::vector<int>& rhs)-> bool {
                  return lhs[0] < rhs[0] || lhs[0] == rhs[0] && lhs[1] < rhs[1];
              });

    std::vector<std::vector<int>> ret = {};

    int index = 0;
    while (index < intervals.size()) {
        int start = intervals[index][0];
        int end = intervals[index][1];
        int p = index + 1;

        while (p < intervals.size() && intervals[p][0] <= end) {
            end = std::max(intervals[p++][1], end);
        }

        ret.push_back(std::vector<int>{start, end});
        index = p;
    }

    return ret;
}
