#include "Solution253.h"

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

class S253IntervalIndexComparator {
public:
    S253IntervalIndexComparator(const std::vector<std::vector<int>>& intervals) : _intervals(intervals) {
    }

    bool operator()(int lhs, int rhs) {
        return _intervals[lhs][1] > _intervals[rhs][1];
    }

private:
    const std::vector<std::vector<int>>& _intervals;
};

int Solution253::minMeetingRooms(std::vector<std::vector<int>>& intervals) {
    std::sort(intervals.begin(),
              intervals.end(),
              [](const std::vector<int>& a, const std::vector<int>& b) {
                  return a[0] < b[0] ||
                      (a[0] == b[0] && a[1] < b[1]);
              });
    const int n = intervals.size();

    size_t max_req = 0;
    auto visited_index_queue = std::priority_queue<int,
                                                   std::vector<int>,
                                                   S253IntervalIndexComparator>(
        S253IntervalIndexComparator(intervals));

    int focus_index = 0;
    while (focus_index < n) {
        int curr_start = intervals[focus_index][0];

        while (focus_index < n
            && intervals[focus_index][0] == curr_start) {
            visited_index_queue.push(focus_index);
            ++focus_index;
        }

        while (!visited_index_queue.empty()
            && intervals[visited_index_queue.top()][1] <= curr_start) {
            visited_index_queue.pop();
        }

        if (visited_index_queue.size() > max_req) {
            max_req = visited_index_queue.size();
        }
    }

    return static_cast<int>(max_req);
}
