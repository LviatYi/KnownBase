#include "Main.h"

#include <iostream>
#include "Solutions.h"
#include <string>

using namespace std;

int main() {
    Solution3 solution;

    string s = " ";
    int i = solution.lengthOfLongestSubstring(s);
    cout << i;

    return 1;
}
