#pragma once
#include <vector>

class Swordii90 {
private:
    int sub_rob(std::vector<int>& nums, int start, int end);
public:
    int rob(std::vector<int>& nums);
};
