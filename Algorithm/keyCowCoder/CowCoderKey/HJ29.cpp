#include <iostream>

char encode(const char c) {
    if (std::isalpha(c)) {
        if (std::isupper(c)) {
            char res = c - 'A' + 'a' + 1;
            return res > 'z' ? 'a' : res;
        } else {
            char res = c - 'a' + 'A' + 1;
            return res > 'Z' ? 'A' : res;
        }
    } else {
        char res = c + 1;
        return res > '9' ? '0' : res;
    }
}

char decode(const char c) {
    if (std::isalpha(c)) {
        if (std::isupper(c)) {
            char res = c - 'A' + 'a' - 1;
            return res < 'a' ? 'z' : res;
        } else {
            char res = c - 'a' + 'A' - 1;
            return res < 'A' ? 'Z' : res;
        }
    } else {
        char res = c - 1;
        return res < '0' ? '9' : res;
    }
}

int hj29() {
    std::string input;

    std::cin >> input;
    for (char c : input) {
        std::cout << encode(c);
    }

    std::cout << std::endl;

    std::cin >> input;
    for (char c : input) {
        std::cout << decode(c);
    }
    return 0;
}
