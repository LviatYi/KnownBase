#pragma once

#include <map>

class Solution146 {
    struct Solution146Node {
        int key;
        int val;
        Solution146Node* next;
        Solution146Node* pre;

        Solution146Node(int _key, int _val, Solution146Node* _next = nullptr, Solution146Node* _pre = nullptr) :
            key(_key), val(_val), next(_next), pre(_pre) {
        }
    };

private:
    std::map<int, Solution146Node*> map_;
    int size_;
    int lowest_heat_key_;
    Solution146Node* heat_link_head_;

    void update_heat(int key);

public:
    Solution146(int capacity);

    int get(int key);

    void put(int key, int value);
};
