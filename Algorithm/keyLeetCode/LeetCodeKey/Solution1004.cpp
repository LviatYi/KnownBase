#include "Solution1004.h"

int Solution1004::longestOnes(std::vector<int>& nums, int k) {
    int p_start = 0;
    int k_life = k;
    int max_len = 0;

    for (int p_end = 1; p_end <= nums.size(); ++p_end) {
        if (nums[p_end - 1] == 0) {
            --k_life;
        }

        while (k_life < 0) {
            if (nums[p_start] == 0) {
                ++k_life;
            }
            ++p_start;
        }
        if (p_end - p_start > max_len) {
            max_len = p_end - p_start;
        }
    }

    return max_len;
}
