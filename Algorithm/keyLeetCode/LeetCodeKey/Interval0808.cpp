#include "Interval0808.h"

#include <array>

void Interval0808::dfs(std::vector<std::string>& result,
                       std::array<int, 52>& char_table,
                       std::string curr,
                       int target_length) {
    if (curr.size() == target_length) {
        result.push_back(curr);
        return;
    }

    for (int i = 0; i < 52; ++i) {
        if (char_table[i] > 0) {
            --char_table[i];
            curr.push_back(i >= 26 ? 'A' + i-26 : 'a' + i);
            dfs(result, char_table, curr, target_length);
            curr.pop_back();
            ++char_table[i];
        }
    }
}

std::vector<std::string> Interval0808::permutation(std::string S) {
    auto result = std::vector<std::string>();
    auto char_table = std::array<int, 52>();

    for (auto c : S) {
        if (std::isupper(c)) {
            ++char_table[c - 'A' + 26];
        } else {
            ++char_table[c - 'a'];
        }
    }

    dfs(result, char_table, "", S.size());

    return result;
}
