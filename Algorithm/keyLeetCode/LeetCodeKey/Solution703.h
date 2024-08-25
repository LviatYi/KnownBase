#pragma once
#include <queue>
#include <vector>

class Solution703 {
private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> front_;
    int k_;
public:
    Solution703(int k, std::vector<int>& nums);

    int add(int val);
};
