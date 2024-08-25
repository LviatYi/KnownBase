#include "Swordii32.h"

bool Swordii32::isAnagram(std::string s, std::string t) {
    if (s.size() != t.size()) {
        return false;
    }

    int char_table[26] = {0};
    bool is_same = true;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] != t[i]) {
            is_same = false;
        }

        ++char_table[s[i] - 'a'];
        --char_table[t[i] - 'a'];
    }

    if (is_same) {
        return false;
    }

    for (int i : char_table) {
        if (i != 0) {
            return false;
        }
    }
    return true;
}
