#include "Solution242.h"

bool Solution242::isAnagram(std::string s, std::string t) {
    if (s.size() != t.size()) {
        return false;
    }
    int char_table[26] = {0};
    for (int i = 0; i < s.size(); ++i) {
        ++char_table[s[i] - 'a'];
        --char_table[t[i] - 'a'];
    }

    for (int i : char_table) {
        if (i != 0) {
            return false;
        }
    }
    return true;
}
