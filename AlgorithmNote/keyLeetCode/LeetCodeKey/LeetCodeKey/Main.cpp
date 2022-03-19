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
    Solution27 solution;

    vector<int> nums = { 0,1,2,2,3,0,4,2 };

    cout << solution.removeElement(nums, 2);

    return 1;
}