#pragma once
//Definition for singly-linked list.
//struct ListNode;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution2 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);
};

