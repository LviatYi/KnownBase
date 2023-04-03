#pragma once
#include <string>
#include <vector>

class Swordii65 {
private:
    struct Character_dict {
        static constexpr int size = 26;

        Character_dict* chars[size] = {nullptr};
        int end_index = -1;
    };

    Character_dict* dict_ = new Character_dict;

    void dfs(Character_dict* current,
             const std::vector<std::string>& words,
             std::vector<int>& contained_string_indexes,
             std::string& current_word,
             std::string& s,
             std::vector<int>& indices);
public:
    int minimumLengthEncoding(std::vector<std::string>& words);
};
