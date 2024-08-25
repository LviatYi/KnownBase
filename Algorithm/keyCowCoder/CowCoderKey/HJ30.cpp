#include <algorithm>
#include <iostream>

void solve1(std::string& str, int n) {
    std::string temp;
    int j = 0;
    for (int i = n; i < str.length(); i += 2) {
        temp += str[i];
    }
    sort(temp.begin(), temp.end());
    for (int i = n; i < str.length(); i += 2) {
        str[i] = temp[j];
        j++;
    }
}

//for循环第三个条件要使i改变
char solvenu(int temp) {
    int nu = 1;
    std::string t;
    int change = 0;
    char r;
    for (int i = 0; i < 4; i++) {
        if (nu & temp) {
            t += '1';
        } else {
            t += '0';
        }
        nu = nu << 1;
    }
    int count = 3;
    for (auto a : t) {
        change += (a - '0') * pow(2, count);
        count--;
    }
    if (change < 10) {
        r = ('0' + change);
    } else {
        r = ('A' + (change - 10));
    }
    return r;
}

int hj30() {
    std::string str1, str2;
    std::cin >> str1 >> str2;
    str1 += str2;
    solve1(str1, 0);
    solve1(str1, 1);
    std::string res;
    for (auto a : str1) {
        if (a <= '9' && a >= '0') {
            int temp = a - '0';
            res += solvenu(temp);
        } else if (a <= 'f' && a >= 'a') {
            int temp = a - 'a' + 10;
            res += solvenu(temp);
        } else if (a <= 'F' && a >= 'A') {
            int temp = a - 'A' + 10;
            res += solvenu(temp);
        } else {
            res += a;
        }
    }
    std::cout << res;
    return 0;
}
