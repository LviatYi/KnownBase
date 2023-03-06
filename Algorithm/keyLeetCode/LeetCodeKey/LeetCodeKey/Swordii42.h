#pragma once
#include <queue>

class Swordii42 {
private:
    const int retention_ = 3000;
    std::queue<int> queue_;
public:
    Swordii42();
    int ping(int t);
};
