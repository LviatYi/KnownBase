#pragma once
#include<stack>
using std::stack;

class Solution155 {
private:
    stack<int> container;
    stack<int> mins;

public:
    Solution155();

    void push(int x);

    void pop();

    int top();

    int min();
};

