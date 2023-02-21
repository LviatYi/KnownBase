#pragma once

class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;

    Node(int _val);
};


class Solution430 {
private:
    Node* subFlatten(Node* head);
public:
    Node* flatten(Node* head);
    Node* flatten2(Node* head);
};
