#include "Solution814.h"

bool Solution814::needCutSub(TreeNode* sub) {
    if (!sub) {
        return false;
    }

    if (sub->left && needCutSub(sub->left)) {
        // delete sub->left;
        sub->left = nullptr;
    }

    if (sub->right && needCutSub(sub->right)) {
        // delete sub->right;
        sub->right = nullptr;
    }
    return !sub->left && !sub->right && sub->val == 0;
}

TreeNode* Solution814::pruneTree(TreeNode* root) {
    if (needCutSub(root)) {
        // delete root;
        return nullptr;
    }

    return root;
}
