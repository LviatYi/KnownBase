#pragma once
#include <queue>
#include <vector>

class Swordii60 {
public:
    void qsort(std::vector<std::pair<int, int>>& v, int start, int end, std::vector<int>& ret, int k);
    std::vector<int> topKFrequent(std::vector<int>& nums, int k);
};
