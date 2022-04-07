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
    Sword31 solution;
    vector<int> pushed = { 1,2,3,4,5 };
    vector<int> popped = { 4,5,3,2,1 };

    cout << solution.validateStackSequences2(pushed, popped);

    return 1;
}