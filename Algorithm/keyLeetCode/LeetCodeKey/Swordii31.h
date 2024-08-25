#pragma once
#include <map>

class Swordii31 {
    struct Swordii31Node {
        int key;
        int val;
        Swordii31Node* next;
        Swordii31Node* pre;

        Swordii31Node(int _key, int _val, Swordii31Node* _next = nullptr, Swordii31Node* _pre = nullptr) :
            key(_key), val(_val), next(_next), pre(_pre) {
        }
    };

private:
    std::map<int, Swordii31Node*> map_;
    int size_;
    int lowest_heat_key_;
    Swordii31Node* heat_link_head_;

    void update_heat(int key);

public:
    Swordii31(int capacity);

    int get(int key);

    void put(int key, int value);
};
