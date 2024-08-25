#include "Solution953.h"

#include <set>

int Solution953::compare(char table[], std::string& lhs, std::string& rhs) {
    int min_size = std::min(lhs.size(), rhs.size());

    for (int i = 0; i < min_size; ++i) {
        switch (compare(table, lhs[i], rhs[i])) {
        case 1:
            return 1;
        case -1:
            return -1;
        default: ;
        }
    }
    return lhs.size() == rhs.size() ? 0 : lhs.size() < rhs.size() ? -1 : 1;
}

int Solution953::compare(char table[], char& lhs, char& rhs) {
    if (table[lhs - 'a'] == table[rhs - 'a']) {
        return 0;
    }
    if (table[lhs - 'a'] > table[rhs - 'a']) {
        return 1;
    }
    return -1;
}


bool Solution953::isAlienSorted(std::vector<std::string>& words, std::string order) {
    char table[26];

    for (int i = 0; i < order.size(); ++i) {
        table[order[i] - 'a'] = i;
    }

    for (int i = 0; i < words.size() - 1; ++i) {
        if (compare(table, words[i], words[i + 1]) == 1) {
            return false;
        }
    }
    return true;
}
