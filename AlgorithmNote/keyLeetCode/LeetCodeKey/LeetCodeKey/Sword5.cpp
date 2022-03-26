#include "Sword5.h"

string Sword5::replaceSpace(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            s.erase(i, 1);
            s.insert(i, "%20");
        }
    }
    return s;
}
