#pragma once
#include <string>
#include <vector>

class Swordii64 {
private:
    struct character_dict {
        static constexpr int size = 26;

        character_dict* chars[size] = {nullptr};
        bool is_end = false;
    };

    character_dict* dict;

    bool sub_search(std::string& searchWord, size_t index, character_dict* current, int tolerance);

public:
    /** Initialize your data structure here. */
    Swordii64();

    void buildDict(std::vector<std::string> dictionary);

    bool search(std::string searchWord);
};
