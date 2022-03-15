#include "Main.h"
#include "Solutions.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    Solution14 solution;

    vector<string>strs = { "" };

    cout << solution.longestCommonPrefix(strs);

    return 1;
}