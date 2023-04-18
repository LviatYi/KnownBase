#include "Solution115.h"

#include <vector>

int Solution115::numDistinct(std::string s, std::string t) {
    int m = s.size();
    int n = t.size();
    std::vector<unsigned long long> dp_roll_last(n);
    std::vector<unsigned long long> dp_roll_current(n);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j <= i && j < n; ++j) {
            dp_roll_current[j] = (i - 1 >= 0
                                      ? dp_roll_last[j]
                                      : 0) + (s[i] == t[j]
                                                  ? (i - 1 >= 0 && j - 1 >= 0
                                                         ? dp_roll_last[j - 1]
                                                         : 1)
                                                  : 0);
        }

        std::swap(dp_roll_current, dp_roll_last);
    }
    return dp_roll_last[n - 1];
}
