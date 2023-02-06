#include "Swordii15.h"

std::vector<int> Swordii15::find_anagrams(std::string s, std::string p) {
    std::vector<int> ret = {};

    int* chars = new int[26];

    for (int i = 0; i < 26; i++) {
        chars[i] = -1;
    }

    for (char c : p) {
        if (chars[c - 'a'] == -1) {
            chars[c - 'a'] = 1;
        }
        else {
            ++chars[c - 'a'];
        }
    }

    int begin = 0;
    int end = 0;
    int unmatch_count = p.size();

    while (begin < s.size() && end < s.size()) {
        if (chars[s[end] - 'a'] != -1) {
            if (chars[s[end] - 'a']) {
                --chars[s[end] - 'a'];
                --unmatch_count;
                ++end;
            }
            else if (s[begin] == s[end]) {
                ++begin;
                ++end;
            }
            else {
                while (chars[s[end] - 'a'] < 1) {
                    chars[s[begin] - 'a']++;
                    ++unmatch_count;
                    ++begin;
                }
            }
        }
        else {
            while (begin < end) {
                chars[s[begin] - 'a']++;
                ++unmatch_count;
                ++begin;
            }

            ++end;
            begin = end;
        }
        if (!unmatch_count) {
            ret.push_back(begin);
        }
    }

    return ret;
}
