#include "Swordii19.h"

bool Swordii19::validPalindrome(const std::string& s, int begin, int end, int fault_tolerance_value) {
    while (begin < end) {
        if (s[begin] == s[end - 1]) {
            ++begin;
            --end;
        }
        else if (fault_tolerance_value > 0) {
            return validPalindrome(s, begin, end - 1, fault_tolerance_value - 1) || validPalindrome(
                s, begin + 1, end, fault_tolerance_value - 1);
        }
        else {
            break;
        }
    }
    return begin >= end;
}

bool Swordii19::validPalindrome(std::string s) {
    return validPalindrome(s, 0, s.size(), 1);
}
