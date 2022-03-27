#include "Sword9.h"

Sword9::Sword9() {
}

void Sword9::appendTail(int value) {
    stack1.push(value);
}

int Sword9::deleteHead() {
    int popElem = -1;
    if (!stack2.empty()) {
        popElem = stack2.top();
        stack2.pop();
    }
    else if (!stack1.empty()) {
        while (!stack1.empty()) {
            stack2.push(stack1.top());
            stack1.pop();
        }
        popElem = stack2.top();
        stack2.pop();
    }
    return popElem;
}
