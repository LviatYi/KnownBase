#include "Solution1702.h"

std::string Solution1702::maximumBinaryString(std::string binary) {
    size_t first_zero = binary.find_first_of('0');
    if (first_zero == std::string::npos) {
        return binary;
    }

    size_t zero_count = std::count(binary.begin(), binary.end(), '0');

    if (zero_count < 2) {
        return binary;
    }

    auto str = std::string(binary.size(), '1');
    str[first_zero + zero_count - 1] = '0';
    return str;
}
