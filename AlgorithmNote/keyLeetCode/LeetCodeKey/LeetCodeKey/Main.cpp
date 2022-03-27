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
    Sword7 solution;

    vector<int> preorder = { 3,9,20,15,7 };
    vector<int>inorder = { 9,3,15,20,7 };

    solution.buildTree(preorder, inorder);

    return 1;
}