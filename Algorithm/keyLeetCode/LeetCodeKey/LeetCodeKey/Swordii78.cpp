#include "Swordii78.h"

ListNode* Swordii78::mergeLists(ListNode* lhs, ListNode* rhs) {
    ListNode* p_head = new ListNode;
    ListNode* current = p_head;
    ListNode* p_l = lhs;
    ListNode* p_r = rhs;

    while (p_l != nullptr || p_r != nullptr) {
        if (p_l == nullptr) {
            current->next = p_r;
            break;
        }
        if (p_r == nullptr) {
            current->next = p_l;
            break;
        }

        if (p_l->val < p_r->val) {
            current->next = p_l;
            p_l = p_l->next;
        }
        else {
            current->next = p_r;
            p_r = p_r->next;
        }
        current = current->next;
    }

    return p_head->next;
}

ListNode* Swordii78::mergeKLists(std::vector<ListNode*>& lists) {
    if (lists.empty()) {
        return nullptr;
    }

    int i = 1;
    while (i <= lists.size()) {
        for (int j = 0; i * j < lists.size(); j += 2) {
            if (j * i + i < lists.size()) {
                lists[j * i] = mergeLists(lists[j * i], lists[j * i + i]);
            }
        }
        i <<= 1;
    }

    return lists[0];
}
