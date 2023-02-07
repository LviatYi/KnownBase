#include "Swordii17.h"

std::string Swordii17::minWindow(std::string s, std::string t) {
    int* hash = new int [58];

    for (int i = 0; i < 58; ++i) {
        hash[i] = INT_MIN;
    }

    int unmatchedCount = t.size();

    for (const char c : t) {
        if (hash[c - 'A'] == INT_MIN) {
            hash[c - 'A'] = 1;
        }
        else {
            hash[c - 'A']++;
        }
    }

    int begin = 0;
    int end = 0;

    int min_begin = 0;
    int min_length = INT_MAX;

    while (true) {
        while (unmatchedCount > 0 && end < s.size()) {
            if (hash[s[end] - 'A'] > INT_MIN) {
                if (hash[s[end] - 'A'] > 0) {
                    --unmatchedCount;
                }
                --hash[s[end] - 'A'];
            }
            end++;
        }

        while (begin < end && hash[s[begin] - 'A'] < 0) {
            if (hash[s[begin] - 'A'] > INT_MIN) {
                hash[s[begin] - 'A']++;
            }
            ++begin;
        }

        if (unmatchedCount == 0 && min_length > end - begin) {
            min_begin = begin;
            min_length = end - begin;
        }

        if (end < s.size()) {
            //if (hash[s[end]) - 'A'] > INT_MIN) {
            //    --hash[s[end]) - 'A'];
            //}
            //++end;
            if (hash[s[begin] - 'A'] > INT_MIN) {
                hash[s[begin] - 'A']++;
            }
            ++begin;
            ++unmatchedCount;
        }
        else {
            break;
        }
    }

    return min_length <= s.size() ? s.substr(min_begin, min_length) : "";
}
