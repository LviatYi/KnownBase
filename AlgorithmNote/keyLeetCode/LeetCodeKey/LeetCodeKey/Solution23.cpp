#include "Solution23.h"
#include "ListNode.h"
#include <queue>

using namespace std;

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
