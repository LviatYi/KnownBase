#include <cctype>
#include <cstddef>
#include <iostream>
#include <map>
#include <string>

using namespace std;


int hj21() {
    map<char, int> table{
        {'a', 2}, {'b', 2}, {'c', 2},
        {'d', 3}, {'e', 3}, {'f', 3},
        {'g', 4}, {'h', 4}, {'i', 4},
        {'j', 5}, {'k', 5}, {'l', 5},
        {'m', 6}, {'n', 6}, {'o', 6},
        {'p', 7}, {'q', 7}, {'r', 7}, {'s', 7},
        {'t', 8}, {'u', 8}, {'v', 8},
        {'w', 9}, {'x', 9}, {'y', 9}, {'z', 9},
    };

    char c;
    while (cin >> c) {
        if (c == '\n')continue;
        if (std::islower(c)) {
            std::cout << char('0' + table[c]);
        } else if (std::isupper(c)) {
            auto code = c - 'A' + 'a' + 1;
            std::cout << char(code > 'z'
                                  ? 'a'
                                  : code);
        } else {
            std::cout << c;
        }
    }
    return 0;
}
