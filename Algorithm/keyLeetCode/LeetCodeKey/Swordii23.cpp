#include "Swordii23.h"

ListNode* Swordii23::getIntersectionNode(ListNode* headA, ListNode* headB) {
    ListNode* p_a = headA;
    ListNode* p_b = headB;
    bool a_cycle = false;
    bool b_cycle = false;

    while (true) {
        if (p_a == p_b) {
            return p_a;
        }

        if (p_a->next) {
            p_a = p_a->next;
        }
        else if (!a_cycle) {
            p_a = headB;
            a_cycle = true;
        }
        else {
            break;
        }

        if (p_b->next) {
            p_b = p_b->next;
        }
        else if (!b_cycle) {
            p_b = headA;
            b_cycle = true;
        }
        else {
            break;
        }
    }
    return nullptr;
}
