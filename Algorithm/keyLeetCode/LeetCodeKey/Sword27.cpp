#include "Sword27.h"

static void swapNode(TreeNode*& n) {
    if (n) {
        TreeNode* t = n->left;
        n->left = n->right;
        n->right = t;
    }
}

TreeNode* Sword27::mirrorTree(TreeNode* root) {
    if (!root) {
        return nullptr;
    }

    swapNode(root);

    mirrorTree(root->left);
    mirrorTree(root->right);

    return root;
}
