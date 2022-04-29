#include "Solution226.h"
static void swapNode(TreeNode*& n) {
    if (n) {
        TreeNode* t = n->left;
        n->left = n->right;
        n->right = t;
    }
}

TreeNode* Solution226::invertTree(TreeNode* root) {
    if (!root) {
        return nullptr;
    }

    swapNode(root);

    invertTree(root->left);
    invertTree(root->right);

    return root;
}