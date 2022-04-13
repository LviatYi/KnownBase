#include "Sword52.h"
#include<vector>

using std::vector;

#pragma region 二次遍历
ListNode* Sword52::getIntersectionNode(ListNode* headA, ListNode* headB) {
    vector< ListNode*> aList;
    vector< ListNode*> bList;
    ListNode* pA = headA;
    ListNode* pB = headB;

    while (pA) {
        aList.push_back(pA);
        pA = pA->next;
    }
    while (pB) {
        bList.push_back(pB);
        pB = pB->next;
    }

    vector<ListNode*>::reverse_iterator aLast = aList.rbegin();
    vector<ListNode*>::reverse_iterator bLast = bList.rbegin();
    ListNode* same = nullptr;

    while (aLast != aList.rend() && bLast != bList.rend() && *aLast == *bLast) {
        same = *aLast;
        aLast++;
        bLast++;
    }

    return same;
}
#pragma endregion
#pragma region 哈希
// 当非公共节点数量少时 相较于官方题解效率有优势，否则反之。
#include<unordered_set>

using std::unordered_set;

static bool setInsert(unordered_set<ListNode*>& set, ListNode* p) {
    if (set.find(p) == set.end()) {
        set.insert(p);
        return true;
    }
    else {
        return false;
    }
}

ListNode* Sword52::getIntersectionNode2(ListNode* headA, ListNode* headB) {
    unordered_set<ListNode*> set;
    ListNode* pA = headA;
    ListNode* pB = headB;

    while (pA || pB) {
        if (pA) {
            if (!setInsert(set, pA)) {
                return pA;
            }
            pA = pA->next;
        }
        if (pB) {
            if (!setInsert(set, pB)) {
                return pB;
            }
            pB = pB->next;
        }
    }
    return nullptr;
}
#pragma endregion
#pragma region 双指针
// 同途同归，异难易缘
ListNode* Sword52::getIntersectionNode3(ListNode* headA, ListNode* headB) {
        ListNode* pA = headA;
        ListNode* pB = headB;
        bool pACanContinue = true;
        bool pBCanContinue = true;

        while (pA != nullptr && pB != nullptr && pA != pB) {
            if (pACanContinue && !pA->next) {
                pA = headB;
                pACanContinue = false;
            }
            else {
                pA = pA->next;
            }
            if (pBCanContinue && !pB->next) {
                pB = headA;
                pBCanContinue = false;
            }
            else {
                pB = pB->next;
            }
        }
        return pA;
    }
#pragma endregion


