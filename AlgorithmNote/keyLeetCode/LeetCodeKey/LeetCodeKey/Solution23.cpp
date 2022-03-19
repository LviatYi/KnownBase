#include "Solution23.h"
#include "ListNode.h"
#include <queue>

using namespace std;

#pragma region 优先队列
// 自定义类型
// 若使用 greater 仿函数则需重载 >
// 若使用 less 仿函数则需重载 <
struct ListNodeComp {
    int val;
    ListNode* pNode;
    bool operator >(const ListNodeComp& listNodeComp2) const {
        return val > listNodeComp2.val;
    }

    ListNodeComp(ListNode node) :val(node.val), pNode(&node) {

    };

    ListNodeComp(ListNode* pNode) :val(pNode->val), pNode(pNode) {

    };
};

ListNode* Solution23::mergeKLists(std::vector<ListNode*>& lists) {
    // 优先队列
    // 元素类型，内部容器（默认为 vector<T>），比较类（仿函数）（默认为 less<T>）
    priority_queue<ListNodeComp, vector<ListNodeComp>, greater<ListNodeComp>> queue;
    ListNode* preAnsHead = new ListNode;
    ListNode* pAns = preAnsHead;
    for (ListNode* pNode : lists) {
        if (pNode) {
            queue.push(ListNodeComp(pNode));
        }
    }

    while (!queue.empty()) {
        pAns->next = queue.top().pNode;
        pAns = pAns->next;
        queue.pop();
        if (pAns->next) {
            queue.push(ListNodeComp(pAns->next));
        }
    }

    return preAnsHead->next;
}
#pragma endregion

#pragma region 二分合并
ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
    if ((!a) || (!b)) return a ? a : b;
    ListNode head, * tail = &head, * aPtr = a, * bPtr = b;
    while (aPtr && bPtr) {
        if (aPtr->val < bPtr->val) {
            tail->next = aPtr; aPtr = aPtr->next;
        }
        else {
            tail->next = bPtr; bPtr = bPtr->next;
        }
        tail = tail->next;
    }
    tail->next = (aPtr ? aPtr : bPtr);
    return head.next;
}

ListNode* merge(vector <ListNode*>& lists, int l, int r) {
    if (l == r) return lists[l];
    if (l > r) return nullptr;
    int mid = (l + r) >> 1;
    return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
}

ListNode* Solution23::mergeKLists2(vector<ListNode*>& lists) {
    return merge(lists, 0, lists.size() - 1);
}
#pragma endregion
