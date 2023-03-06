#pragma once

class Solution346 {
private:
    int* numbers_;
    int capacity_;
    int length_;
    int tail_;
    int sum_;
public:
    /** Initialize your data structure here. */
    Solution346(int size);

    double next(int val);
};
