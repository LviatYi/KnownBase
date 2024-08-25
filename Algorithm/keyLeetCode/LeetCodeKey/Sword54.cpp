#include "Sword54.h"

int invInOrder(TreeNode* root, int& k) {
    if (!root) {
        return -1;
    }
    int right = invInOrder(root->right, k);
    if (right != -1) {
        return right;
    }
    if (k == 1) {
        return root->val;
    }
    k--;

    return invInOrder(root->left, k);
}

int Sword54::kthLargest(TreeNode* root, int k) {
    return invInOrder(root, k);
}
