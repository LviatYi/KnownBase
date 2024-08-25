#include "Swordii16.h"

#include <unordered_set>

int Swordii16::lengthOfLongestSubstring(std::string s) {
    std::unordered_set<char> occ;
    int n = s.size();
    int rk = -1, ans = 0;
    for (int i = 0; i < n; ++i) {
        if (i != 0) {
            occ.erase(s[i - 1]);
        }
        while (rk + 1 < n && !occ.count(s[rk + 1])) {
            occ.insert(s[rk + 1]);
            ++rk;
        }
        ans = std::max(ans, rk - i + 1);
    }
    return ans;
}
