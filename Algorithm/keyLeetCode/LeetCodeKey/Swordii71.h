#pragma once
#include <vector>

class Swordii71 {
private:
    std::vector<int> _w_sum;
public:
    Swordii71(std::vector<int>& w);

    int pickIndex();
};
