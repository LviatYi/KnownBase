#pragma once
#include<stack>
using std::stack;
class Sword9 {
private:
    stack<int>stack1;
    stack<int>stack2;
public:
    Sword9();

    void appendTail(int value);

    int deleteHead();
};

