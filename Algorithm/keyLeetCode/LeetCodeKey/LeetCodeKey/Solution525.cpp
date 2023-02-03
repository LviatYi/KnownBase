#include "Solution525.h"

#include <unordered_map>

int Solution525::findMaxLength(std::vector<int>& nums) {
    auto map = std::unordered_map<int, int>();

    int pre_sum = 0;
    int ans = 0;
    for (int i = 0; i < nums.size(); ++i) {
        pre_sum += nums[i] == 0 ? -1 : 1;


        if (pre_sum == 0) {
            ans = i + 1;
        }
        else {
            auto start = map.find(pre_sum);

            if (start == map.end()) {
                map.insert(std::pair<int, int>(pre_sum, i));
            }
            else {
                ans = ans < i - start->second ? i - start->second : ans;
            }
        }
    }
    return ans;
}
