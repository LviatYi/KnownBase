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
    Solution30 solution;

    string str = "barfoothefoobarman";
    vector<string>words = { "foo","bar" };
    vector<int>ans;

    ans = solution.findSubstring(str, words);

    for (int i : ans) {
        cout << i << endl;
    }

    return 1;
}