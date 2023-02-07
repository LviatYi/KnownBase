#include "Swordii24.h"


ListNode* Swordii24::reverseList(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    ListNode* pre_head = new ListNode(0, head);
    ListNode* former = pre_head;
    ListNode* middle = head;
    ListNode* latter = head->next;
    ListNode* p = latter->next;

    do {
        former->next = latter;
        middle->next = latter->next;
        latter->next = middle;
    }
    while (latter->next);

    return nullptr;
}
