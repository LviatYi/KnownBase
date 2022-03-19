#include "Solution24.h"

ListNode* Solution24::swapPairs(ListNode* head) {
    ListNode* preAnsNode = new ListNode(0, head);
    ListNode* pNode = new ListNode(0, preAnsNode);

    while (pNode->next->next && pNode->next->next->next) {
        ListNode* temp1 = pNode->next;
        ListNode* temp2 = pNode->next->next;
        ListNode* temp3 = pNode->next->next->next;
        ListNode* temp4 = pNode->next->next->next->next;
        temp1->next = temp3;
        temp2->next = temp4;
        temp3->next = temp2;
        pNode->next = temp2;
    }

    return preAnsNode->next;
}
