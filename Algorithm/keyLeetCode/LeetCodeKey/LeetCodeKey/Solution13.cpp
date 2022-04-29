#include "Solution13.h"

int Solution13::romanToInt(string s) {
    char last = 0;
    int result = 0;

    for (char c : s) {
        switch (c) {
        case 'I':
            result += 1;
            break;

        case'V':
            if (last == 'I') {
                result += 3;
            }
            else result += 5;
            break;

        case'X':
            if (last == 'I') {
                result += 8;
            }
            else result += 10;
            break;

        case'L':
            if (last == 'X') {
                result += 30;
            }
            else result += 50;
            break;

        case'C':
            if (last == 'X') {
                result += 80;
            }
            else result += 100;
            break;

        case'D':
            if (last == 'C') {
                result += 300;
            }
            else result += 500;
            break;

        case'M':
            if (last == 'C') {
                result += 800;
            }
            else result += 1000;
            break;

        default:
            break;
        }
        last = c;
    }
    return result;
}
