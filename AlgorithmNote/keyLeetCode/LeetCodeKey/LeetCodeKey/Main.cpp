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
    Sword51 solution;

    vector<int> nums = { 7,5,6,4 };

    int sum = solution.reversePairs(nums);

    return sum;
}