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
    Solution24 solution;

    ListNode* head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4))));

    ListNode* ans = solution.swapPairs(head);

    return 1;
}