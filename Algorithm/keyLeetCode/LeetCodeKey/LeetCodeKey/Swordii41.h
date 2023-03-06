#pragma once

class Swordii41 {
private:
    int* numbers_;
    int capacity_;
    int length_;
    int tail_;
    int sum_;
public:
    /** Initialize your data structure here. */
    Swordii41(int size);

    double next(int val);
};
