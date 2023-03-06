#include "Solution226.h"

static void swapNode(Swordii43TreeNode*& n) {
    if (n) {
        Swordii43TreeNode* t = n->left;
        n->left = n->right;
        n->right = t;
    }
}

Swordii43TreeNode* Solution226::invertTree(Swordii43TreeNode* root) {
    if (!root) {
        return nullptr;
    }

    swapNode(root);

    invertTree(root->left);
    invertTree(root->right);

    return root;
}
