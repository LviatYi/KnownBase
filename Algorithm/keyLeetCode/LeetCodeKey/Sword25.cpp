#include "Sword25.h"

ListNode* Sword25::mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode* preAnsHead = new ListNode();
    ListNode* pAns = preAnsHead;
    ListNode* i = l1;
    ListNode* j = l2;

    while (i != nullptr && j != nullptr) {
        if (i->val <= j->val) {
            pAns->next = i;
            i = i->next;
            pAns = pAns->next;
        }
        else {
            pAns->next = j;
            j = j->next;
            pAns = pAns->next;
        }
    }
    if (i != nullptr) {
        pAns->next = i;
    }
    else if (j != nullptr) {
        pAns->next = j;
    }
    return preAnsHead->next;
}
