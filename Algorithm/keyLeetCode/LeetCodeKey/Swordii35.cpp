#include "Swordii35.h"

#include <algorithm>

int Swordii35::findMinDifference(std::vector<std::string>& timePoints) {
    if (timePoints.size() > 60 * 24) {
        return 0;
    }
    std::vector<int> times = {};

    times.reserve(timePoints.size());
    for (auto time_point : timePoints) {
        times.push_back(
            ((time_point[0] - '0') * 10 + (time_point[1] - '0')) * 60 +
            (time_point[3] - '0') * 10 +
            (time_point[4] - '0'));
    }

    std::sort(times.begin(), times.end());

    int min_time = *times.begin() - *(times.end() - 1) + 24 * 60;

    for (int i = 0; i < times.size() - 1; ++i) {
        int current_time = times[i + 1] - times[i];
        min_time = current_time < min_time ? current_time : min_time;
    }
    return min_time;
}
