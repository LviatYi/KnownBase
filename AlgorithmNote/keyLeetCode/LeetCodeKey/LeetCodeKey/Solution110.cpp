#include "Solution110.h"
#include <algorithm>

#pragma region Solution110_1
int Solution110::maxDepth(TreeNode* root) {
    if (!root) {
        return 0;
    }

    int left = maxDepth(root->left) + 1;
    int right = maxDepth(root->right) + 1;

    if (left > right) {
        return left;
    }
    else {
        return right;
    }
}
#pragma endregion

#pragma region Solution110_2
using std::max;
using std::abs;

static int isSubBalance(TreeNode* root) {
    if (!root) {
        return 0;
    }
    int lHeight = isSubBalance(root->left);
    if (lHeight < 0) {
        return lHeight;
    }
    int rHeight = isSubBalance(root->right);
    if (rHeight < 0) {
        return rHeight;
    }

    return abs(lHeight - rHeight) < 2 ? max(lHeight, rHeight) + 1 : -1;
}

bool Solution110::isBalanced(TreeNode* root) {
    return isSubBalance(root) != -1;
}
#pragma endregion


