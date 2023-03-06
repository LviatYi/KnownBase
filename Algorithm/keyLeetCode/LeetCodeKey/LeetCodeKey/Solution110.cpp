#include "Solution110.h"
#include <algorithm>

using std::max;
using std::abs;

static int isSubBalance(Swordii43TreeNode* root) {
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

bool Solution110::isBalanced(Swordii43TreeNode* root) {
    return isSubBalance(root) != -1;
}
