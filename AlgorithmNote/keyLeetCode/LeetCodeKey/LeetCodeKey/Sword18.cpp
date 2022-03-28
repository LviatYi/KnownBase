#include "Sword18.h"

ListNode* Sword18::deleteNode(ListNode* head, int val) {
    ListNode* p = head;
    ListNode* preHead = new ListNode(0, head);
    ListNode* last = preHead;
    while (p != nullptr) {
        if (p->val == val) {
            last->next = p->next;
            break;
        }
        last = p;
        p = p->next;
    }

    return preHead->next;
}
