#include "Solution209.h"

int Solution209::minSubArrayLen(int target, std::vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }

    auto begin = nums.begin();
    auto end = nums.begin() + 1;

    int min_length = INT32_MAX;
    int current_sum = *begin;
    int current_length = 1;

    while (begin != nums.end()) {
        if (current_sum < target) {
            if (end == nums.end()) {
                break;
            }
            current_sum += *end;
            current_length++;
            ++end;
        }
        else {
            min_length = min_length < current_length ? min_length : current_length;

            current_sum -= *begin;
            current_length--;
            ++begin;
        }
    }
    return min_length == INT32_MAX ? 0 : min_length;
}
