#include "Swordii29.h"

Swordii29::Node* Swordii29::insert(Node* head, int insertVal) {
    if (!head) {
        auto ret = new Node(insertVal);
        ret->next = ret;
        return ret;
    }

    Node* p = head;
    Node* next = p->next;

    do {
        if ((p->val <= next->val && p->val <= insertVal && next->val >= insertVal) || (p->val > next->val && (p->val <=
            insertVal || next->val > insertVal))) {
            p->next = new Node(insertVal, p->next);
            return head;
        }

        p = p->next;
        next = p->next;

    }
    while (p != head);

    p->next = new Node(insertVal, p->next);
    return head;
}
