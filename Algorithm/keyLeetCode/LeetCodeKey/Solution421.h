#pragma once
#include <vector>

class Solution421 {
private:
    struct Character_dict {
        static constexpr int size = 2;

        Character_dict* chars[size] = {nullptr};

        void insert(int val, int index = sizeof(int) * 8 - 1);
    };

    Character_dict* dict_ = new Character_dict;

public:
    int findMaximumXOR(std::vector<int>& nums);
};
