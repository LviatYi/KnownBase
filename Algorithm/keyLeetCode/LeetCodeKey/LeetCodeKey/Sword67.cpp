#include "Sword67.h"

int Sword67::strToInt(string str) {
        // 直接解
        long long ans = 0;
        bool flag = false;

        // 擦除前段非数字字符
        str.erase(0, str.find_first_not_of(" "));

        if (str[0] == '-') {
            flag = true;
            str.erase(str.begin());
        }
        else if (str[0] == '+') {
            str.erase(str.begin());
        }

        int i = 0;
        while (i < str.length() && str[i] <= '9' && str[i] >= '0') {
            ans = ans < (LLONG_MAX - str[i]) / 10 ? ans * 10 + str[i] - '0' : LLONG_MAX;
            i++;
        }

        if (ans > INT_MAX) {
            return flag ? INT_MIN : INT_MAX;
        }
        else {
            return flag ? int(-ans) : int(ans);
        }
}

int Sword67::strToInt2(string str) {
    // 自动机

    Automaton automaton;
    for (char c : str)
        automaton.get(c);
    return automaton.sign * automaton.ans;
}

AtoiStatus Automaton::getStatus(char c) {
    if (isspace(c)) return AtoiStatus::start;
    if (c == '+' or c == '-') return AtoiStatus::sign;
    if (isdigit(c)) return AtoiStatus::number;
    return AtoiStatus::end;
}

void Automaton::get(char c) {
    state = table[state][getStatus(c)];
    if (state == AtoiStatus::number) {
        ans = ans * 10 + c - '0';
        ans = sign == 1 ? min(ans, (long long)INT_MAX) : min(ans, -(long long)INT_MIN);
    }
    else if (state == AtoiStatus::sign)
        sign = c == '+' ? 1 : -1;

}
