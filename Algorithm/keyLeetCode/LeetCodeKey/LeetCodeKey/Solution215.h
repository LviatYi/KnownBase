#pragma once
#include <vector>

class Solution215 {
private:
    void quick_sort(std::vector<int>& container, int begin, int end, int target);
public:
    int findKthLargest(std::vector<int>& nums, int k);
};
