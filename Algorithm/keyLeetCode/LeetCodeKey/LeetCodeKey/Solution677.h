#pragma once
#include <string>

class Solution677 {
private:
    struct Character_dict {
        static constexpr int size = 26;

        Character_dict* chars[size] = {nullptr};
        int val = 0;

        void insert(std::string& word, const int& end_val, int index = 0);
    };

    Character_dict* dict_;
public:
    Solution677();

    void insert(std::string key, int val);

    int sum(std::string prefix);
};
