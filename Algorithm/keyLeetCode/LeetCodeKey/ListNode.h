#pragma once

struct ListNode {
    int val;
    ListNode* next;
    ListNode* pre;
    ListNode() : val(0), next(nullptr), pre(nullptr) {}
    ListNode(int x) : val(x), next(nullptr), pre(nullptr) {}
    ListNode(int x, ListNode* _next) : val(x), next(_next), pre(nullptr) {}
    ListNode(int x, ListNode* _next, ListNode* _pre) : val(x), next(_next), pre(_pre) {}
};
