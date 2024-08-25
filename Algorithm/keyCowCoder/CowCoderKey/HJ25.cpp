#include <algorithm>
#include <iostream>
#include <unordered_set>

bool num_include(unsigned int num,
                 unsigned int flag,
                 unsigned long long scale_factor) {
    while (num > 0) {
        if (num % scale_factor == flag) {
            return true;
        }

        num /= 10;
    }
    return false;
}

unsigned long long get_num_scale_factor(unsigned int flag) {
    long long res = 10;
    while (res <= flag) {
        res *= 10;
    }

    return res;
}

int hj25() {
    size_t size;

    std::cin >> size;
    std::vector<unsigned int>i_list(size);
    for (size_t i = 0; i < size; ++i) {
        std::cin >> i_list[i];
    }
    std::cin >> size;
    std::vector<unsigned int>r_list(size);
    for (size_t i = 0; i < size; ++i) {
        std::cin >> r_list[i];
    }

    std::sort(r_list.begin(), r_list.end());
    auto p = std::unique(r_list.begin(), r_list.end());
    r_list.erase(p, r_list.end());

    std::vector<unsigned int> output;
    for (int c : r_list) {
        std::vector<unsigned int> sub_output;
        const auto scale_factor = get_num_scale_factor(c);
        for (int j = 0; j < i_list.size(); j++) {
            if (num_include(i_list[j], c, scale_factor)) {
                sub_output.push_back(j);
                sub_output.push_back(i_list[j]);
            }
        }

        if (sub_output.size() > 0) {
            output.push_back(c);
            output.push_back(sub_output.size() / 2);
            output.insert(
                output.end(),
                sub_output.begin(),
                sub_output.end());
        }
    }

    std::cout << output.size();
    for (auto elem : output) {
        std::cout << " " << elem;
    }

    return 0;
}
