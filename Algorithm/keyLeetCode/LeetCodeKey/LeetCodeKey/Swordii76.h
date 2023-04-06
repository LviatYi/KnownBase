#pragma once
#include <vector>

class Swordii76 {
private:
    void quick_sort(std::vector<int>& container, int begin, int end, int target);
public:
    int findKthLargest(std::vector<int>& nums, int k);
    int findKthLargest2(std::vector<int>& nums, int k);
};
