#include "Solution10.h"
#include <vector>

using namespace std;

bool Solution10::isMatch(char sc, char pc) {
    return sc == pc || pc == '.';
}

bool Solution10::isMatch(string s, string p) {
    int m = s.size();
    int n = p.size();

    // 从空串开始，因此长度 +1
    vector<vector<int>> f(m + 1, vector<int>(n + 1));
    f[0][0] = true;
    for (int i = 0; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*') {
                f[i][j] |= f[i][j - 2];
                if (i > 0 && isMatch(s[i - 1], p[j - 2])) {
                    f[i][j] |= f[i - 1][j];
                }
            }
            else {
                if (i > 0 && isMatch(s[i - 1], p[j - 1])) {
                    f[i][j] |= f[i - 1][j - 1];
                }
            }
        }
    }
    return f[m][n];
}
