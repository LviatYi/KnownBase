#include "Solution21.h"

ListNode* Solution21::mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode* preAnsHead = new ListNode();
    ListNode* pAns = preAnsHead;
    ListNode* i = list1;
    ListNode* j = list2;

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
