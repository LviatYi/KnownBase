#pragma once
#include <vector>

class Swordii74 {
private:
    class Schedule_cmp {
    public:
        bool operator()(const std::vector<int>& lhs, const std::vector<int>& rhs) const {
            return lhs[0] < rhs[0] || lhs[0] == rhs[0] && lhs[1] < rhs[1];
        }
    };

public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals);
};
