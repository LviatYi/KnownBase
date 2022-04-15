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
    Sword59 solution;
    vector<int> nums{ 1,-1 };
    solution.maxSlidingWindow(nums, 1);

    return 0;
}