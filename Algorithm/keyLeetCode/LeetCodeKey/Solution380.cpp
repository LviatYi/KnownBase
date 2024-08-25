#include "Solution380.h"


/** Initialize your data structure here. */
Solution380::Solution380() {
    hash_ = {};
    vector_ = {};
}

/** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
bool Solution380::insert(int val) {
    if (hash_.count(val) > 0) {
        return false;
    }
    hash_[val] = vector_.size();
    vector_.push_back(val);

    return true;
}

/** Removes a value from the set. Returns true if the set contained the specified element. */
bool Solution380::remove(int val) {
    if (hash_.count(val) <= 0) {
        return false;
    }

    vector_[hash_[val]] = vector_.back();
    hash_[vector_.back()] = hash_[val];

    vector_.pop_back();
    hash_.erase(val);
    return true;
}

/** Get a random element from the set. */
int Solution380::getRandom() {
    return vector_[rand() % (vector_.size())];
}
