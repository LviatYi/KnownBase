#include "Sword24.h"
#include<stack>

using std::stack;

#pragma region 栈
ListNode* Sword24::reverseList(ListNode* head) {
    stack<ListNode*> s;
    ListNode* p = head;
    while (p != nullptr) {
        s.push(p);
        p = p->next;
    }
    ListNode* preHead = new ListNode();
    p = preHead;
    while (!s.empty()) {
        p->next = s.top();
        s.pop();
        p = p->next;
    }

    p->next = nullptr;

    return preHead->next;
}
#pragma endregion

#pragma region 直接倒置
ListNode* Sword24::reverseList2(ListNode* head) {
    ListNode* last = head;
    if (head == nullptr) {
        return nullptr;
    }
    ListNode* curr = head->next;
    ListNode* t;

    while (curr != nullptr) {
        t = curr->next;
        curr->next = last;
        last = curr;
        curr = t;
    }

    head->next = nullptr;

    return last;
}
#pragma endregion


