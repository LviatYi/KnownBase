#include "Main.h"

#include <iostream>
#include "Solutions.h"

using namespace std;

int main() {
    Solution2 solution;

    ListNode* l1 = new ListNode(2, new ListNode(4, new ListNode(3)));
    ListNode* l2 = new ListNode(5, new ListNode(6, new ListNode(4)));
    ListNode* ans = solution.addTwoNumbers(l1, l2);

    cout
        << ans->val << ' '
        << ans->next->val << ' '
        << ans->next->next->val << ' '
        << endl;

    return 1;
}
