#include "Solution1450.h"

#include <vector>
#include <unordered_map>

using namespace std;

int Solution1450::busyStudent(std::vector<int>& startTime, std::vector<int>& endTime, int queryTime) {
    int count = 0;
    const int n = startTime.size();

    for (int i = 0; i < n; ++i) {
        if (startTime[i] <= queryTime && endTime[i] >= queryTime) {
            ++count;
        }
    }
    return count;
}
