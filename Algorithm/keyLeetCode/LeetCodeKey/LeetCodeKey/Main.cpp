#include "Main.h"
#include "Solutions.h"
#include "LeetcodeUtil.h"
#include "ListNode.h"
#include "TreeNode.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>

using namespace std;

int main() {
    int val = 2;
    vector int_list = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    std::vector<std::vector<int>> int_list_list = LeetcodeUtil::deserialize_vector_vector(
        "[[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]");

    std::string str = "010010";
    std::vector<string> strings = {"time", "me", "bell"};

    TreeNode* tree = LeetcodeUtil::level_order_deserialize_tree_node("8,6,10,5,7,9,11");

    ListNode* list_node = LeetcodeUtil::deserialize_list_node("[1,4,5]");
    vector<ListNode*> list_node_list = LeetcodeUtil::deserialize_vector_list_node("[[1,4,5], [1,3,4], [2,6]]");

    Swordii88 solution;
    //Swordii73 solution(vector);

    //auto ret = solution.book();

    auto ret = solution.minCostClimbingStairs(int_list);

    //Node* head = new Node(1, new Node(2, new Node(3, new Node(4))));

    //auto ans = solution.reorderList2(head);
    //solution.reorderList2(head);

    //cout << "done" << ", return " << ret << endl;
}
