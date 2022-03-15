#pragma once
#include <string>

using namespace std;

class Solution12 {
private:
    pair<int, string> valueSymbols[13] = {
        {1000, "M"},
        {900,  "CM"},
        {500,  "D"},
        {400,  "CD"},
        {100,  "C"},
        {90,   "XC"},
        {50,   "L"},
        {40,   "XL"},
        {10,   "X"},
        {9,    "IX"},
        {5,    "V"},
        {4,    "IV"},
        {1,    "I"}
    };

public:
    string intToRoman(int num);
    string intToRoman2(int num);
};



