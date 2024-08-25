#include "Solution25.h"
#include <memory>

ListNode* Solution25::reverseKGroup(ListNode* head, int k) {
    ListNode* preHead = new ListNode(0, head);
    ListNode* pNode = preHead;
    ListNode** cycleTable;

    cycleTable = (ListNode**)malloc(sizeof(ListNode*) * (k + 1));

    while (true) {
        bool isContinue = true;
        ListNode* j = pNode->next;
        for (int i = 0; i < k + 1; i++) {
            if (!j && i != k) {
                isContinue = false;
                break;
            }
            else {
                cycleTable[i] = j;
                if (j) {
                    j = j->next;
                }
            }
        }

        if (isContinue) {
            cycleTable[0]->next = cycleTable[k];
            for (int i = 0; i < k - 1; i++) {
                cycleTable[k - i - 1]->next = cycleTable[k - i - 2];
            }
            pNode->next = cycleTable[k - 1];
        }
        else {
            break;
        }
        pNode = cycleTable[0];
    }

    free(cycleTable);

    return preHead->next;
}
