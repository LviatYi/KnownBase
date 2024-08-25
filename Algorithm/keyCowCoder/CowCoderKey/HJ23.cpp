#include <iostream>
#include <unordered_set>

using namespace std;


int hj23() {
    std::string input;
    while (cin >> input) {
        int record[26] = {0};
        for (char c : input) {
            ++record[c - 'a'];
        }
        int min = INT_MAX;
        unordered_set<char> chars;
        for (int i = 0; i < 26; ++i) {
            if (0 != record[i] && record[i] < min) {
                min = record[i];
                chars.clear();
                chars.insert(i + 'a');
            } else if (record[i] == min) {
                chars.insert(i + 'a');
            }
        }

        for (char c : input) {
            if (chars.find(c) != chars.end()) {
                continue;
            }
            std::cout << c;
        }
    }
    return 0;
}
