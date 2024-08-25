#include "Swordii12.h"

#include <numeric>

int Swordii12::pivotIndex(std::vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }

    int total_sum = std::accumulate(nums.begin(), nums.end(), 0);
    int sum = 0;

    for (int i = 0; i < nums.size(); ++i) {
        if (2 * sum + nums[i] == total_sum) {
            return i;
        }

        sum += nums[i];
    }

    return -1;
}
