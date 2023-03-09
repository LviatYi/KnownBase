#include "Main.h"
#include "Solutions.h"
#include "LeetcodeUtil.h"
#include "ListNode.h"
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

int main() {
    //string in = "[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]";'

    //auto input = LeetcodeUtil::deserialize_vector_vector(in);

    Swordii50 solution = {};

    TreeNode* root = new TreeNode(
        10,
        new TreeNode(5,
                     new TreeNode(3,
                                  new TreeNode(3),
                                  new TreeNode(-2)),
                     new TreeNode(2,
                                  nullptr,
                                  new TreeNode(1))),
        new TreeNode(-3,
                     nullptr,
                     new TreeNode(11)));

    auto ret = solution.pathSum(root, 8);

    //Node* head = new Node(1, new Node(2, new Node(3, new Node(4))));

    //auto ans = solution.reorderList2(head);
    //solution.reorderList2(head);

    cout << "done" << endl;

}
