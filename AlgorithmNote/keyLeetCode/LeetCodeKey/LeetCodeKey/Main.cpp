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
    Sword21 solution;

    vector<int> nums = { 1,2,2,4,3,5,6,6,3,5,6,1 };

    nums = solution.exchange(nums);

    return 1;
}