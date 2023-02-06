#include "LeetcodeUtil.h"

std::vector<std::vector<int>> LeetcodeUtil::deserialization_vector_vector(std::string in) {
    std::vector<std::vector<int>> ret = {};

    if (in.empty()) {
        return ret;
    }

    in.erase(std::remove_if(in.begin(), in.end(), isspace), in.end());

    int squareBracketCount = 0;

    bool element_valid = false;
    bool vector_valid = false;
    int number = 0;
    std::vector<int> current_vector = std::vector<int>();


    for (int i = 0; i < in.size(); ++i) {
        if (in[i] == '[') {
            element_valid = true;
            vector_valid = true;
            --squareBracketCount;
        }
        else if (std::isdigit(in[i])) {
            number *= 10;
            number += in[i] - '0';
        }

        else if (in[i] == ',' || in[i] == ']') {
            if (element_valid) {
                current_vector.push_back(number);
                number = 0;
            }

            if (in[i] == ']') {
                --squareBracketCount;
                if (vector_valid) {
                    ret.push_back(current_vector);
                    current_vector.clear();
                }
                element_valid = false;
                vector_valid = false;
            }
        }
    }

    if (~squareBracketCount) {
        return ret;
    }
    return {};
}
