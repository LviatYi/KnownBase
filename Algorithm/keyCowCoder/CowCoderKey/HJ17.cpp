#include "Solutions.h"
#include <iostream>
#include <regex>
#include <string>
#include <vector>

int hj17() {
    std::string input;
    // A10;S20;W10;D30;X;A1A;B10A11;;A10;
    while (std::cin >> input) {
        std::vector<std::pair<char, int>> directions{};
        std::string token;
        size_t pos = 0;
        while (pos < input.size()) {
            size_t result = input.find(';', pos);
            if (result == std::string::npos) {
                result = input.size();
            }

            token = input.substr(pos, result - pos);
            if (!token.empty()) {
                std::regex pattern(R"(^([WASD])([0-9]+)$)");
                std::smatch match_result;
                if (std::regex_match(token, match_result, pattern)) {
                    directions.emplace_back(
                        match_result[1].str()[0],
                        std::stoi(match_result[2].str())
                    );
                }
            }

            pos = result + 1;
        }


        std::pair<int, int> dest = {0, 0};
        for (const auto& [d,s] : directions) {
            switch (d) {
            case 'W':
                dest.second += s;
                break;
            case 'A':
                dest.first -= s;
                break;
            case 'S':
                dest.second -= s;
                break;
            case 'D':
                dest.first += s;
                break;
            default:
                break;
            }
        }

        std::cout << dest.first << "," << dest.second << std::endl;
    }

    return 0;
}
