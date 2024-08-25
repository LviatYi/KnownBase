#pragma once
#include <string>

class Swordii19 {
private:
    bool validPalindrome(const std::string& s, int begin, int end, int fault_tolerance_value);

public:
    bool validPalindrome(std::string s);
};
