#pragma once
#include <cstddef>

class Solution708 {

    class Node {
    public:
        int val;
        Node* next;

        Node() {
        }

        Node(int _val) {
            val = _val;
            next = NULL;
        }

        Node(int _val, Node* _next) {
            val = _val;
            next = _next;
        }
    };

public:
    Node* insert(Node* head, int insertVal);
};
