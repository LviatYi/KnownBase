#include "Main.h"
#include "Solutions.h"
#include "ListNode.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

int main() {
    Solution23 solution;

    vector<ListNode*> lists{
        new ListNode(1,new ListNode(4,new ListNode(5))),
        new ListNode(1,new ListNode(3,new ListNode(4))),
        new ListNode(2,new ListNode(6))
    };

    ListNode* head = solution.mergeKLists(lists);

    return 1;
}