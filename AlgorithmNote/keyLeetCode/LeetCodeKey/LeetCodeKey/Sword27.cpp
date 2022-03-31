#include "Sword27.h"

TreeNode* Sword27::mirrorTree(TreeNode* root) {
    if (!root) {
        return;
    }

    swapNode(root);

    mirrorTree(root->left);
    mirrorTree(root->right);

    return root;
}

static void swapNode(TreeNode*& n) {
    if (n) {
        TreeNode* t = n->left;
        n->left = n->right;
        n->right = t;
    }
}
