#include "Main.h"
#include "Solutions.h"
#include "LeetcodeUtil.h"
#include "ListNode.h"
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>

using namespace std;

int main() {
    //string in = "[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]";'

    //auto input = LeetcodeUtil::deserialize_vector_vector(in);

    int val = 2;
    vector<int> vector = {2, 2};
    std::vector<string> strings = {"time", "me", "bell"};
    TreeNode* tree = LeetcodeUtil::level_order_deserialize_tree_node("8,6,10,5,7,9,11");

    Swordii73 solution;
    //Swordii73 solution(vector);

    //auto ret = solution.book();

    auto ret = solution.minEatingSpeed(vector, val);
    //Node* head = new Node(1, new Node(2, new Node(3, new Node(4))));

    //auto ans = solution.reorderList2(head);
    //solution.reorderList2(head);

    //cout << "done" << ", return " << ret << endl;
}
