#include "Sword20.h"
#include<vector>

using std::vector;

static bool matchInt(string& s, string::iterator& p) {
    string::iterator t = p;
    if (*p == '+' || *p == '-') {
        p++;
    }
    if (p == s.end() || !isdigit(*p)) {
        p = t;
        return false;
    }

    while (p != s.end() && isdigit(*p)) {
        p++;
    }
    return true;
}

static bool matchDec(string& s, string::iterator& p) {
    string::iterator t = p;
    bool hasNum = false;
    if (*p == '+' || *p == '-') {
        p++;
    }
    if (matchInt(s, p)) {
        hasNum = true;
    }
    if (p == s.end() || !(*p++ == '.')) {
        p = t;
        return false;
    }
    if (*p != '+' && *p != '-' && matchInt(s, p)) {
        hasNum = true;
    }

    if (hasNum) {
        return true;
    }
    else {
        p = t;
        return false;
    }
}

bool Sword20::isNumber(string s) {
    auto p = s.begin();

    while (p != s.end() && *p == ' ') {
        p++;
    }

    if (!(matchDec(s, p) || matchInt(s, p))) {
        return false;
    }

    if (p != s.end() && (*p == 'e' || *p == 'E')) {
        p++;
        if (!matchInt(s, p)) {
            return false;
        }
    }

    while (p != s.end() && *p == ' ') {
        p++;
    }

    if (p != s.end()) {
        return false;
    }

    return true;
}