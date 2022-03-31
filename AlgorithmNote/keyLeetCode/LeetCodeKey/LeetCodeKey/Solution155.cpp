#include "Solution155.h"

Solution155::Solution155() {
}

void Solution155::push(int x) {
    if (this->mins.empty() || this->mins.top() >= x) {
        this->mins.push(x);
    }
    this->container.push(x);
}

void Solution155::pop() {
    if (this->container.empty()) {
        return;
    }
    if (!this->mins.empty() && this->container.top() == this->mins.top()) {
        this->mins.pop();
    }
    this->container.pop();
}

int Solution155::top() {
    return this->container.top();
}

int Solution155::min() {
    return this->mins.top();
}
