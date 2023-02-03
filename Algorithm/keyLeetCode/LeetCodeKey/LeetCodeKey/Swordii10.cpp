#include "Swordii10.h"

#include <unordered_map>

int Swordii10::subarraySum(std::vector<int>& nums, int k) {
    std::unordered_map<int, int> mp;
    mp[0] = 1;
    int count = 0, pre = 0;
    for (auto& x : nums) {
        pre += x;
        if (mp.find(pre - k) != mp.end()) {
            count += mp[pre - k];
        }
        mp[pre]++;
    }
    return count;
}
