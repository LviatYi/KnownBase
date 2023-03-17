#include "Solution2389.h"

#include <algorithm>

std::vector<int> Solution2389::answerQueries(std::vector<int>& nums, std::vector<int>& queries) {
    std::sort(nums.begin(), nums.end());
    int i = 1;

    for (int i = 1; i < nums.size(); ++i) {
        nums[i] += nums[i - 1];
    }

    std::vector<int> ret(queries.size());
    i = 0;
    for (int query : queries) {
        ret[i++] = std::upper_bound(nums.begin(), nums.end(), query) - nums.begin();
    }

    return ret;
}
