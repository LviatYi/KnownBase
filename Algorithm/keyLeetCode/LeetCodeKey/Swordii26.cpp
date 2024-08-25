#include "Swordii26.h"

#include <stack>

#pragma region 栈

void Swordii26::reorderList(ListNode* head) {
    if (!head) {
        return;
    }
    std::stack<ListNode*> stack = {};
    ListNode* p = head;
    int count = 0;

    while (p) {
        stack.push(p);
        p = p->next;
        count++;
    }

    p = head;

    for (int i = 0; i < count / 2; ++i) {
        ListNode* temp = p->next;

        p->next = stack.top();
        p->next->next = temp;
        stack.pop();
        p = temp;
    }

    if (count % 2) {
        p->next = nullptr;
    }
    else {
        p->next->next = nullptr;
    }

    return;
}

#pragma endregion

#pragma region 快慢指针

void Swordii26::reorderList2(ListNode* head) {
    if (!head || !head->next || !head->next->next) {
        return;
    }

    ListNode* slow_p = head;
    ListNode* fast_p = head;

    while (fast_p->next && fast_p->next->next) {
        slow_p = slow_p->next;
        fast_p = fast_p->next->next;
    }

    ListNode* reversed = slow_p->next;
    ListNode* p_reverse = reversed;

    if (p_reverse && p_reverse->next) {
        while (p_reverse->next) {
            ListNode* temp = p_reverse->next->next;
            p_reverse->next->next = reversed;
            reversed = p_reverse->next;
            p_reverse->next = temp;
        }
    }

    slow_p->next = nullptr;

    ListNode* p = head;
    p_reverse = reversed;

    while (p != nullptr) {
        ListNode* temp = p->next;
        ListNode* temp2 = nullptr;

        p->next = p_reverse;
        if (p_reverse) {
            temp2 = p_reverse->next;
            p_reverse->next = temp;
        }

        p = temp;
        p_reverse = temp2;
    }
}

#pragma endregion
