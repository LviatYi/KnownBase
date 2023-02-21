#pragma once
#include "ListNode.h"

class Solution234 {
private:
    ListNode* front;
    bool checkIsPalindrome(ListNode* p);

public:
    bool isPalindrome(ListNode* head);
    bool isPalindrome2(ListNode* head);
};
