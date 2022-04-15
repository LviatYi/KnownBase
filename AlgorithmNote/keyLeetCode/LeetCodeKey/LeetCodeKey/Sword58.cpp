#include "Sword58.h"

string Sword58::reverseWords(string s) {
    string ans;
    string::iterator begin = s.end() - 1;
    string::iterator end = s.end();

    while (begin != s.begin() - 1) {
        if (*begin == ' ') {
            if (begin + 1 != end) {
                ans += string(begin + 1, end) + " ";
            }
            end = begin;
        }
        begin--;
    }
    ans += string(begin + 1, end);
    if (!ans.empty() && ans.at(ans.size() - 1) == ' ') {
        ans.erase(ans.size() - 1, 1);
    }

    return ans;
}
