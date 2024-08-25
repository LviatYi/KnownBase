#include "Swordii30.h"

#include <iostream>

Swordii30::Swordii30() {
    hash_ = {};
    vector_ = {};
}

bool Swordii30::insert(int val) {
    if (hash_.count(val) > 0) {
        return false;
    }
    hash_[val] = vector_.size();
    vector_.push_back(val);

    return true;
}

bool Swordii30::remove(int val) {
    if (hash_.count(val) <= 0) {
        return false;
    }

    vector_[hash_[val]] = vector_.back();
    hash_[vector_.back()] = hash_[val];

    vector_.pop_back();
    hash_.erase(val);
    return true;
}

int Swordii30::getRandom() {
    return vector_[rand() % (vector_.size())];
}
