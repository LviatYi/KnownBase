#include "Main.h"
#include "Solutions.h"
#include "ListNode.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

int main() {
    Solution39 solution;

    vector<int>candidates = { 2,3,6,7 };
    int target = 7;

    vector<vector<int>> ans;

    ans = solution.combinationSum(candidates, target);

    return 1;
}