#include "Solution14.h"

string Solution14::longestCommonPrefix(vector<string>& strs) {
    string ans = "";
    for (int i = 0; ; i++) {
        char c = strs[0][i];
        for (int j = 0; j < strs.size(); j++) {
            if (strs[j] == "" || (i < strs[j].length() && c != strs[j][i]) || i >= strs[j].length()) {
                return ans;
            }
        }
        ans += c;
    }
    return ans;
}
