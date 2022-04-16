#pragma once
#include<vector>
#include<queue>
#include<deque>
using std::vector;
using std::queue;
using std::deque;

class Sword59 {
private:
    deque<int> maxValue;
    queue<int> q;
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k);
    vector<int> maxSlidingWindow2(vector<int>& nums, int k);

    Sword59();
    int max_value();
    void push_back(int value);
    int pop_front();
};

