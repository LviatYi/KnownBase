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
    Sword33 solution;
    vector<int> v = { 1, 2, 3, 4, 5 };

    cout << solution.verifyPostorder(v);

    return 1;
}