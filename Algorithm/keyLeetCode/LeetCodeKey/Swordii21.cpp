#include "Swordii21.h"

#include <vector>

int Swordii21::getLength(ListNode* head) {
    int length = 0;
    while (head) {
        ++length;
        head = head->next;
    }
    return length;
}

ListNode* Swordii21::removeNthFromEnd(ListNode* head, int n) {
    ListNode* dummy = new ListNode(0, head);
    int length = getLength(head);
    ListNode* cur = dummy;
    for (int i = 1; i < length - n + 1; ++i) {
        cur = cur->next;
    }
    cur->next = cur->next->next;
    ListNode* ans = dummy->next;
    delete dummy;
    return ans;
}
