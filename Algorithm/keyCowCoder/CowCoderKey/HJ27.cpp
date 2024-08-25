#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <unordered_set>

const size_t chars_count = 26;

std::array<int, chars_count> get_table(const std::string& word) {
    std::array<int, chars_count> ret{};

    for (const auto c : word) {
        ++ret[c - 'a'];
    }

    return ret;
}

bool compare(const std::array<int, chars_count>& lhs,
             const std::array<int, chars_count>& rhs) {
    for (int i = 0; i < chars_count; ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

int hj27() {
    int count;
    while (std::cin >> count) {
        std::vector<std::string> words(count);
        for (int i = 0; i < count; ++i) {
            std::cin >> words[i];
        }

        std::string standard;
        int order;
        std::cin >> standard >> order;

        const auto table = get_table(standard);
        std::sort(words.begin(), words.end());
        auto sum = 0;
        int index;
        for (int i = 0; i < words.size(); ++i) {
            const auto& word = words[i];
            if (word.size() != standard.size() ||
                word == standard) {
                continue;
            }

            if (compare(table, get_table(word))) {
                ++sum;
                if (sum == order) {
                    index = i;
                }
            }
        }

        std::cout << sum << std::endl;
        if (index >= 0) {
            std::cout << words[index];
        }
    }

    return 0;
}
