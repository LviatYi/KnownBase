#pragma once
#include <vector>

class Solution213 {
private:
    int sub_rob(std::vector<int>& nums, int start, int end);

public:
    int rob(std::vector<int>& nums);
};
