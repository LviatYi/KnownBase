#include "Solution104.h"

int Solution104::maxDepth(Swordii43TreeNode* root) {
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
