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
    Solution26 solution;

    vector<int> nums = { 0,0,1,1,1,2,2,3,4 };

    cout << solution.removeDuplicates(nums);

    return 1;
}