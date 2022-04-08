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
    Sword36 solution;
    TreeNode* root = new TreeNode(4, new TreeNode(2, new TreeNode(1), new TreeNode(3)), new TreeNode(5));

    solution.treeToDoublyList(root);

    return 1;
}