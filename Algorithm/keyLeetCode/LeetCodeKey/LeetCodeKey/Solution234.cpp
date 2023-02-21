#include "Solution234.h"
#include <stack>

#pragma region 快慢指针 + 栈

bool Solution234::isPalindrome(ListNode* head) {
    if (!head) {
        return true;
    }

    std::stack<ListNode*> s = {};
    ListNode* slow = head;
    ListNode* fast = head;

    while (true) {
        if (!fast) {
            break;
        }
        if (!fast->next) {
            slow = slow->next;
            break;
        }

        s.push(slow);

        slow = slow->next;
        fast = fast->next->next;
    }

    while (!s.empty() && slow != nullptr) {
        if (s.top()->val != slow->val) {
            return false;
        }
        slow = slow->next;
        s.pop();
    }
    return true;
}

#pragma endregion

#pragma region 递归

bool Solution234::checkIsPalindrome(ListNode* p) {
    if (!p) {
        return true;
    }

    if (checkIsPalindrome(p->next)) {
        return p->val == front->val && ((front = front->next) || true);
    }
    return false;
}

bool Solution234::isPalindrome2(ListNode* head) {
    front = head;
    return checkIsPalindrome(head);
}

#pragma endregion
