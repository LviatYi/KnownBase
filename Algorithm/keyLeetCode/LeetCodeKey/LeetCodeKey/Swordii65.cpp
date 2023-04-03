#include "Swordii65.h"

#pragma region 完全解算法
// 以下算法含所有所需解，但在题目下未必是最优解

void Swordii65::dfs(Character_dict* current,
                    const std::vector<std::string>& words,
                    std::vector<int>& contained_string_indexes,
                    std::string& current_word,
                    std::string& s,
                    std::vector<int>& indices) {
    bool is_contained = false;

    if (current->end_index != -1) {
        contained_string_indexes.push_back(current->end_index);
    }

    for (int i = 0; i < Character_dict::size; ++i) {
        if (current->chars[i] != nullptr) {
            is_contained = true;
            current_word.push_back(static_cast<char>('a' + i));
            dfs(current->chars[i],
                words,
                contained_string_indexes,
                current_word,
                s,
                indices);
            current_word.pop_back();
        }
    }
    if (current->end_index != -1 && !is_contained) {
        std::reverse(current_word.begin(), current_word.end());
        s += current_word + "#";
        std::reverse(current_word.begin(), current_word.end());
        for (const int index : contained_string_indexes) {
            indices[index] = s.size() - words[index].size() - 1;
        }
        contained_string_indexes.clear();
    }
}

int Swordii65::minimumLengthEncoding(std::vector<std::string>& words) {
    for (int i = 0; i < words.size(); ++i) {
        auto current = dict_;
        for (int j = words[i].size() - 1; j >= 0; --j) {
            if (current->chars[words[i][j] - 'a'] == nullptr) {
                current->chars[words[i][j] - 'a'] = new Character_dict;
            }

            current = current->chars[words[i][j] - 'a'];
        }
        current->end_index = i;
    }

    auto contained_string_indexes = std::vector<int>();
    auto current_word = std::string("");
    auto s = std::string("");
    auto indices = std::vector<int>(words.size());

    dfs(dict_, words, contained_string_indexes, current_word, s, indices);

    return s.size();
}

#pragma endregion
