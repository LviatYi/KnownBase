#include "Sword6.h"
#include <stack>

vector<int> Sword6::reversePrint(ListNode* head) {
    ListNode* pNode = head;
    std::stack<int> s;
    vector<int>ans;

    while (pNode != nullptr) {
        s.push(pNode->val);
        pNode = pNode->next;
    }

    while (!s.empty()) {
        ans.push_back(s.top());
        s.pop();
    }

    return ans;
}
