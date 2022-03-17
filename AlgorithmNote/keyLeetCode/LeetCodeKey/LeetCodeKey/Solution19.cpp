#include "Solution19.h"
#include <vector>

using namespace std;

ListNode* Solution19::removeNthFromEnd(ListNode* head, int n) {
    if (head->next == nullptr) {
        return nullptr;
    }

    vector<ListNode*> nodeTable;
    ListNode* pNode = head;
    while (pNode != nullptr) {
        nodeTable.push_back(pNode);
        pNode = pNode->next;
    }

    if (n <= nodeTable.size()) {
        delete nodeTable[nodeTable.size() - n];
        if (n == 1) {
            nodeTable[nodeTable.size() - 2]->next = nullptr;
        }
        else if (nodeTable.size() - n > 0) {
            nodeTable[nodeTable.size() - n - 1]->next = nodeTable[nodeTable.size() - n + 1];
        }
        else {
            head = nodeTable[nodeTable.size() - n + 1];
        }
    }
    return head;
}
