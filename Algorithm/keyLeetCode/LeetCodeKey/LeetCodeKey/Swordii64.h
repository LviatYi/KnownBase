#pragma once
#include <string>
#include <vector>

class Swordii64 {
private:
    struct Character_dict {
        static constexpr int size = 26;

        Character_dict* chars[size] = {nullptr};
        bool is_end = false;
    };

    Character_dict* dict_;

    bool sub_search(std::string& searchWord, size_t index, Character_dict* current, int tolerance);

public:
    /** Initialize your data structure here. */
    Swordii64();

    void buildDict(std::vector<std::string> dictionary);

    bool search(std::string searchWord);
};
