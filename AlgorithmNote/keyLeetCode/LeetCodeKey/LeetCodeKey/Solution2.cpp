#include "Solution2.h"

//struct ListNode {
//    int val;
//    ListNode* next;
//    ListNode() : val(0), next(nullptr) {}
//    ListNode(int x) : val(x), next(nullptr) {}
//    ListNode(int x, ListNode* next) : val(x), next(next) {}
//};

ListNode* Solution2::addTwoNumbers(ListNode* l1, ListNode* l2) {
    short carry = 0;
    ListNode* ans = new ListNode();
    ListNode* p1;
    ListNode* p2;
    ListNode* pa;
    p1 = l1;
    p2 = l2;
    pa = ans;

    while (p1 || p2 || carry) {
        pa->next = new ListNode;
        pa = pa->next;
        if (p1) {
            pa->val += p1->val;
            p1 = p1->next;
        }
        if (p2) {
            pa->val += p2->val;
            p2 = p2->next;
        }
        if (carry) {
            pa->val++;
            carry--;
        }
        if (pa->val > 9) {
            pa->val -= 10;
            carry++;
        }
    }

    return ans->next;
}
