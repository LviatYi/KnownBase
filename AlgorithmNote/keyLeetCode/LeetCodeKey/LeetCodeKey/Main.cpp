#include "Main.h"
#include "Solutions.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    Solution15 solution;

    vector<int> key = { 1,-1,-1,0 };
    vector<vector<int>> ans = solution.threeSum(key);

    cout << "hello";

    return 1;
}