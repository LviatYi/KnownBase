#include "Swordii18.h"

bool Swordii18::isPalindrome(std::string s) {
    int begin = 0;
    int end = s.size();

    while (begin < end) {
        while (!(std::isalpha(s[begin]) || std::isalnum(s[begin])) && begin < end) {
            ++begin;
        }
        while (!(std::isalpha(s[end - 1]) || std::isalnum(s[end - 1])) && begin < end) {
            --end;
        }

        if (std::tolower(s[begin]) == std::tolower(s[end - 1])) {
            ++begin;
            --end;
        }
        else {
            break;
        }
    }
    return begin >= end;
}
