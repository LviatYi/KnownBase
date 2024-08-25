#include "Sword33.h"
#include <stack>

using std::stack;
#pragma region 分治法
static bool verifySubPostorder(vector<int>& postorder, int start, int end) {
    if (start >= end - 1) {
        return true;
    }

    int rootVal = postorder[end];

    end--;

    int lStart = start;
    int lEnd = start - 1;
    int rStart = end + 1;
    int rEnd = end;

    while (lEnd < end && postorder[lEnd + 1] < rootVal) {
        lEnd++;
    }
    while (rStart > start && postorder[rStart - 1] > rootVal) {
        rStart--;
    }

    return (lEnd == rStart - 1) && verifySubPostorder(postorder, lStart, lEnd) && verifySubPostorder(postorder, rStart, rEnd);
}

bool Sword33::verifyPostorder(vector<int>& postorder) {
    return verifySubPostorder(postorder, 0, postorder.size() - 1);
}
#pragma endregion

#pragma region 单调栈
bool Sword33::verifyPostorder2(vector<int>& postorder) {
    stack<int> s;
    int root = INT_MAX;

    for (int i = postorder.size() - 1; i >= 0; i++) {
        if (postorder[i] > root) {
            return false;
        }
        while (!s.empty() && s.top() > postorder[i]) {
            root = s.top();
            s.pop();
        }
        s.push(postorder[i]);
    }

    return false;
}
#pragma endregion

