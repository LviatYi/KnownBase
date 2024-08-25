#include "Solution647.h"

int Solution647::countSubstrings(std::string s) {
    int n = s.size();
    std::string t = "$#";
    for (const char& c : s) {
        t += c;
        t += '#';
    }
    n = t.size();
    t += '!';

    auto f = std::vector<int>(n);
    int iMax = 0, rMax = 0, ans = 0;
    for (int i = 1; i < n; ++i) {
        f[i] = (i <= rMax) ? std::min(rMax - i + 1, f[2 * iMax - i]) : 1;
        while (t[i + f[i]] == t[i - f[i]]) ++f[i];
        if (i + f[i] - 1 > rMax) {
            iMax = i;
            rMax = i + f[i] - 1;
        }
        ans += (f[i] / 2);
    }

    return ans;
}
