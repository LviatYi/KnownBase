#include "Swordii41.h"

Swordii41::Swordii41(int size) {
    numbers_ = new int[size]{0};
    capacity_ = size;
    length_ = 0;
    tail_ = 0;
    sum_ = 0;
}

double Swordii41::next(int val) {
    if (tail_ >= capacity_) {
        tail_ = 0;
    }
    if (length_ < capacity_) {
        length_++;
    }
    sum_ -= numbers_[tail_];
    sum_ += val;
    numbers_[tail_] = val;
    tail_++;

    return static_cast<double>(sum_) / length_;
}
