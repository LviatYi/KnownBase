#include "Main.h"
#include "Solutions.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    Solution19 solution;

    ListNode* head = new ListNode(1, new ListNode(2));

    head = solution.removeNthFromEnd(head, 2);

    return 1;
}