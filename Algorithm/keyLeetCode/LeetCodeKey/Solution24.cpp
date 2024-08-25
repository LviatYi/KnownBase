#include "Solution24.h"

ListNode* Solution24::swapPairs(ListNode* head) {
    ListNode* preAnsNode = new ListNode(0, head);
    ListNode* pNode = preAnsNode;

    while (pNode->next && pNode->next->next) {
        ListNode* temp1 = pNode->next;
        ListNode* temp2 = pNode->next->next;
        ListNode* temp3 = pNode->next->next->next;
        pNode->next = temp2;
        temp1->next = temp3;
        temp2->next = temp1;
        pNode = temp1;
    }

    return preAnsNode->next;
}
