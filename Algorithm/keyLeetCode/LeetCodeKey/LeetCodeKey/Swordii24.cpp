#include "Swordii24.h"


ListNode* Swordii24::reverseList(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }

    ListNode* p_head = head;

    while (head->next) {
        ListNode* temp = head->next->next;
        head->next->next = p_head;
        p_head = head->next;
        head->next = temp;
    }

    return p_head;
}
