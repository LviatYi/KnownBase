#include "Solution703.h"

Solution703::Solution703(int k, std::vector<int>& nums) {
    k_ = k;
    if (nums.empty()) {
        return;
    }

    for (int num : nums) {
        add(num);
    }
}

int Solution703::add(int val) {
    if (front_.size() < k_) {
        front_.push(val);
    }
    else {
        front_.push(val);
        front_.pop();
    }
    return front_.top();
}
