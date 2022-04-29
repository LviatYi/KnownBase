#include "Solution12.h"

string Solution12::intToRoman(int num) {
    int i = 0;
    string ans;
    while (num > 0) {
        if (num >= valueSymbols[i].first) {
            num -= valueSymbols[i].first;
            ans += valueSymbols[i].second;
        }
        else {
            i++;
        }
    }
    return ans;
}

string Solution12::intToRoman2(int num) {
    char s[] = "IVXLCDM";
    string result;
    int i = 0;
    while (num) {
        int n = num % 10;
        if (n < 4) {
            result = string(n, s[0 + i]) + result;
        }
        else if (n > 4 && n < 9) {
            result = s[1 + i] + string(n - 5, s[0 + i]) + result;
        }
        else if (n == 4) {
            result = string{ s[0 + i] } + s[1 + i] + result;
        }
        else {
            result = string{ s[0 + i] } + s[2 + i] + result;
        }
        i += 2;
        num = num / 10;
    }
    return result;
}
