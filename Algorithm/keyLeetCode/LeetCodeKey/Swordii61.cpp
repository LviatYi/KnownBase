#include "Swordii61.h"

#include <queue>

std::vector<std::vector<int>> Swordii61::kSmallestPairs(std::vector<int>& nums1, std::vector<int>& nums2, int k) {
    std::vector<std::vector<int>> ret{};
    if (nums1.empty() || nums2.empty()) {
        return ret;
    }

    auto cmp = [&nums1, &nums2](const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
        return nums1[lhs.first] + nums2[lhs.second] > nums1[rhs.first] + nums2[rhs.second];
    };

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> queue(cmp);

    for (int i = 0; i < nums1.size(); ++i) {
        queue.emplace(std::pair<int, int>{i, 0});
    }
    while (k-- > 0 && !queue.empty()) {
        auto vec = queue.top();
        queue.pop();
        ret.push_back({nums1[vec.first], nums2[vec.second]});
        if (vec.second + 1 < nums2.size()) {
            queue.emplace(vec.first, vec.second + 1);
        }
    }

    return ret;
}
