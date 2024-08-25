#pragma once
#include <queue>
#include <vector>

class Swordii59 {
private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> front_;
    int k_;
public:
    Swordii59(int k, std::vector<int>& nums);

    int add(int val);
};
