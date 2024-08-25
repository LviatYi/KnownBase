#pragma once
#include <vector>

#include "ListNode.h"

class Swordii78 {
private:
    ListNode* mergeLists(ListNode* lhs, ListNode* rhs);
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists);
};
