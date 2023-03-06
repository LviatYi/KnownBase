#include "Swordii42.h"

Swordii42::Swordii42() {
    queue_ = {};
}

int Swordii42::ping(int t) {
    queue_.push(t);
    while (queue_.front() < t - retention_) {
        queue_.pop();
    }

    return queue_.size();
}
