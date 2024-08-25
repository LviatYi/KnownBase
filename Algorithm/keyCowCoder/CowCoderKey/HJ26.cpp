#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>

int hj26() {
    std::string input;
    while (std::getline(std::cin, input)) {
        std::vector record(26, std::vector<bool>());
        for (const char c : input) {
            if (std::isalpha(c)) {
                if (std::isupper(c)) {
                    record[c - 'A'].push_back(true);
                } else {
                    record[c - 'a'].push_back(false);
                }
            }
        }

        auto p = 0;
        auto p_vice = 0;
        for (char c : input) {
            if (std::isalpha(c)) {
                while (p < 26 && p_vice >= record[p].size()) {
                    ++p;
                    p_vice = 0;
                }
                std::cout << static_cast<char>(p + (record[p][p_vice]
                                                        ? 'A'
                                                        : 'a'));
                p_vice++;
            } else {
                std::cout << c;
            }
        }
    }

    return 0;
}
