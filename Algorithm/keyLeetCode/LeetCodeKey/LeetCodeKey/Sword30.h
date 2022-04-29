#pragma once
#include<stack>
using std::stack;

class Sword30 {
private:
    stack<int> container;
    stack<int> mins;

public:
    Sword30();

    void push(int x);

    void pop();

    int top();

    int min();
};

