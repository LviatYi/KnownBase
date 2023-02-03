#include "Swordii9.h"

int Swordii9::numSubarrayProductLessThanK(std::vector<int>& nums, int k) {
    int n = nums.size(), ret = 0;
    int prod = 1, i = 0;
    for (int j = 0; j < n; j++) {
        prod *= nums[j];
        while (i <= j && prod >= k) {
            prod /= nums[i];
            i++;
        }
        ret += j - i + 1;
    }
    return ret;
}
