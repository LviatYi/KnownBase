#include "Main.h"
#include "Solutions.h"
#include "ListNode.h"
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

int main() {
    Sword24 solution;

    ListNode* head = new ListNode(1,new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));

    head = solution.reverseList(head);

    return 1;
}