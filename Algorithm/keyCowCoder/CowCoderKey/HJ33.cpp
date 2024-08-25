#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

unsigned int decode_ip(std::string addr) {
    auto result = 0;
    auto p = 0;
    auto last = 0;
    while (true) {
        p = addr.find('.', last);
        result <<= 8;
        result += std::stoi(addr.substr(last, p - last));
        last = p + 1;
        if (p == std::string::npos) {
            break;
        }
    }

    return result;
}

std::string encode_ip(unsigned int val) {
    std::string result;
    while (val > 0) {
        if (result.empty()) {
            result = std::to_string(val % (1 << 8)) ;
        } else {
            result = std::to_string(val % (1 << 8)) + '.' + result;
        }
        val >>= 8;
    }

    return result;
}


int hj33() {
    std::string input;
    std::cin >> input;
    std::cout << decode_ip(input) << std::endl;
    std::cin >> input;
    std::cout << encode_ip(std::stoul(input)) << std::endl;

    return 0;
}
