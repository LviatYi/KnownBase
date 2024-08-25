#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
using namespace std;

void say_ng() {
    std::cout << "NG" << std::endl;
}

void say_ok() {
    std::cout << "OK" << std::endl;
}

int hj20() {
    std::string input;
    while (cin >> input) {
        if (input.size() <= 8) {
            say_ng();
            continue;
        }

        auto has_lower = false;
        auto has_upper = false;
        auto has_num = false;
        auto has_symbol = false;
        for (char c : input) {
            if (std::isalpha(c)) {
                if (!has_upper && std::isupper(c)) {
                    has_upper = true;
                } else if (!has_lower && std::islower(c)) {
                    has_lower = true;
                }
            } else if (std::isdigit(c)) {
                has_num = true;
            } else {
                has_symbol = true;
            }
        }
        size_t count = has_lower +
            has_upper +
            has_num +
            has_symbol;
        if (count < 3) {
            say_ng();
            continue;
        }

        auto has_same = false;
        for (int i = 0; i < input.size() - 6; ++i) {
            for (int j = i + 1; j < input.size() - 3; ++j) {
                if (
                    input[i] == input[j] &&
                    input[i + 1] == input[j + 1] &&
                    input[i + 2] == input[j + 2]
                ) {
                    has_same = true;
                    goto label;
                }
            }
        }
    label:
        if (has_same) {
            say_ng();
        } else {
            say_ok();
        }
    }

    return 0;
}
