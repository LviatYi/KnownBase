#include "Sword50.h"
#include <array>

using std::array;

char Sword50::firstUniqChar(string s) {
        array<int, 26> chars{ 0 };

        for (char c : s) {
            chars[c - 'a']++;
        }

        char once = ' ';
        for (char c : s) {
            if (chars.at(c - 'a') == 1) {
                once = c;
                break;
            }
        }
        return once;
}
