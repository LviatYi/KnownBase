#include "Main.h"
#include "Solutions.h"
#include "LeetcodeUtil.h"
#include "ListNode.h"
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

int main() {
    string in = "[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]";

    auto input = LeetcodeUtil::deserialization_vector_vector(in);

    Swordii16 solution;

    auto ans = solution.lengthOfLongestSubstring("ohvhjdml");

    cout << ans << endl;
}
