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
    Sword4 solution;

    vector<vector<int>> preorder = { {-5} };

    solution.findNumberIn2DArray(preorder, -5);

    return 1;
}