#pragma once
#include <map>
#include <vector>

class Swordii30 {
private:
    std::map<int, unsigned long long> hash_;
    std::vector<int> vector_;
public:
    /** Initialize your data structure here. */
    Swordii30();

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val);

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val);

    /** Get a random element from the set. */
    int getRandom();
};
