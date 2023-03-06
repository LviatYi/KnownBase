#include "Solution933.h"

Solution933::Solution933() {
    queue_ = {};
}

int Solution933::ping(int t) {
    queue_.push(t);
    while (queue_.front() < t - retention_) {
        queue_.pop();
    }

    return queue_.size();
}
