#include "Sword30.h"

Sword30::Sword30() {
}

void Sword30::push(int x) {
    if (this->mins.empty() || this->mins.top() >= x) {
        this->mins.push(x);
    }
    this->container.push(x);
}

void Sword30::pop() {
    if (this->container.empty()) {
        return;
    }
    if (!this->mins.empty() && this->container.top() == this->mins.top()) {
        this->mins.pop();
    }
    this->container.pop();
}

int Sword30::top() {
    return this->container.top();
}

int Sword30::min() {
    return this->mins.top();
}
