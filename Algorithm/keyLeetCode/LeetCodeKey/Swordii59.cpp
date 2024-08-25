#include "Swordii59.h"

Swordii59::Swordii59(int k, std::vector<int>& nums) {
    k_ = k;
    if (nums.empty()) {
        return;
    }

    for (int num : nums) {
        add(num);
    }
}

int Swordii59::add(int val) {
    if (front_.size() < k_) {
        front_.push(val);
    }
    else {
        front_.push(val);
        front_.pop();
    }
    return front_.top();
}
