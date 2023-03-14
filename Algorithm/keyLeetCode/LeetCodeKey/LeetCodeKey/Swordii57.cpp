#include "Swordii57.h"

#include <set>

bool Swordii57::containsNearbyAlmostDuplicate(std::vector<int>& nums, int k, int t) {
    int n = nums.size();
    std::set<int> rec;
    for (int i = 0; i < n; i++) {
        auto iter = rec.lower_bound(nums[i] <= INT_MIN + t ? INT_MIN : nums[i] - t);
        if (iter != rec.end() && *iter <= (nums[i] >= INT_MAX - t ? INT_MAX : nums[i] + t)) {
            return true;
        }
        rec.insert(nums[i]);
        if (i >= k) {
            rec.erase(nums[i - k]);
        }
    }
    return false;
}
