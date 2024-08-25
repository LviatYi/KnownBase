#include "Sword38.h"

static int table[26]{ 0 };
static string currentStr;

void appendChar(int length, vector<string>& ans) {
    if (currentStr.length() == length) {
        ans.push_back(currentStr);
        return;
    }

    for (int i = 0; i < 26; i++) {
        if (table[i] != 0) {
            currentStr.push_back('a' + i);
            table[i]--;

            appendChar(length, ans);

            currentStr.pop_back();
            table[i]++;
        }
    }
}

vector<string> Sword38::permutation(string s) {
    vector<string> ans;
    for (char c : s) {
        table[c - 'a']++;
    }

    appendChar(s.length(), ans);

    return ans;
}