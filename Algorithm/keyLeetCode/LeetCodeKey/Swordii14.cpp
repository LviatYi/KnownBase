#include "Swordii14.h"

#include <unordered_map>

bool Swordii14::checkInclusion(std::string s1, std::string s2) {
    std::unordered_map<char, int> chars = {};

    for (char c : s1) {
        chars[c]++;
    }

    int begin = 0;
    int end = 0;
    int unmatch_count = s1.size();

    while (begin < s2.size() && end < s2.size()) {
        if (chars.count(s2[end])) {
            if (chars[s2[end]]) {
                --chars[s2[end]];
                --unmatch_count;
                ++end;
            }
            else if (s2[begin] == s2[end]) {
                ++begin;
                ++end;
            }
            else {
                while (chars[s2[end]] < 1) {
                    chars[s2[begin]]++;
                    ++unmatch_count;
                    ++begin;
                }
            }
        }
        else {
            while (begin < end) {
                chars[s2[begin]]++;
                ++unmatch_count;
                ++begin;
            }

            ++end;
            begin = end;
        }
        if (!unmatch_count) {
            return true;
        }
    }
    return false;
}

bool Swordii14::checkInclusion2(std::string s1, std::string s2) {
    int* chars = new int[26];

    for (int i = 0; i < 26; i++) {
        chars[i] = -1;
    }

    for (char c : s1) {
        if (chars[c - 'a'] == -1) {
            chars[c - 'a'] = 1;
        }
        else {
            ++chars[c - 'a'];
        }
    }

    int begin = 0;
    int end = 0;
    int unmatch_count = s1.size();

    while (begin < s2.size() && end < s2.size()) {
        if (chars[s2[end] - 'a'] != -1) {
            if (chars[s2[end] - 'a']) {
                --chars[s2[end] - 'a'];
                --unmatch_count;
                ++end;
            }
            else if (s2[begin] == s2[end]) {
                ++begin;
                ++end;
            }
            else {
                while (chars[s2[end] - 'a'] < 1) {
                    chars[s2[begin] - 'a']++;
                    ++unmatch_count;
                    ++begin;
                }
            }
        }
        else {
            while (begin < end) {
                chars[s2[begin] - 'a']++;
                ++unmatch_count;
                ++begin;
            }

            ++end;
            begin = end;
        }
        if (!unmatch_count) {
            return true;
        }
    }
    return false;
}
