#include "Sword22.h"
#include<stack>

using std::stack;

#pragma region 栈
ListNode* Sword22::getKthFromEnd(ListNode* head, int k) {
    stack<ListNode*> s;

    ListNode* p = head;

    while (p != nullptr) {
        s.push(p);
        p = p->next;
    }

    for (int i = 1; i < k; i++) {
        s.pop();
    }
    return s.top();
}
#pragma endregion

#pragma region 差异指针
ListNode* Sword22::getKthFromEnd2(ListNode* head, int k) {
    ListNode* f = head;
    ListNode* s = head;
    for (int i = 1; i < k; i++) {
        f = f->next;
    }
    while (f != nullptr) {
        f = f->next;
        s = s->next;
    }
    return s;
}

#pragma endregion

