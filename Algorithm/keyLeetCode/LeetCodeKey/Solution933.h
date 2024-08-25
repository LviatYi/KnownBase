#pragma once
#include <queue>

class Solution933 {
private:
    const int retention_ = 3000;
    std::queue<int> queue_;
public:
    Solution933();

    int ping(int t);
};
