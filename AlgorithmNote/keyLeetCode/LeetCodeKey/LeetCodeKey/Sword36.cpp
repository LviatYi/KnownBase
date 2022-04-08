#include "Sword36.h"
static TreeNode* inorderWalk(TreeNode* root, TreeNode*& lastNode) {
    if (!root) {
        return nullptr;
    }

    inorderWalk(root->left, lastNode);

    if (lastNode) {
        lastNode->right = root;
    }
    root->left = lastNode;

    lastNode = root;

    if (!root->right) {
        return root;
    }
    else {
        return inorderWalk(root->right, lastNode);
    }
}

TreeNode* Sword36::treeToDoublyList(TreeNode* root) {
    TreeNode* preHead = new TreeNode(0);
    TreeNode* lastNode = preHead;

    TreeNode* last = inorderWalk(root, lastNode);
    if (preHead->right) {
        last->right = preHead->right;
        preHead->right->left = last;
    }

    return preHead->right;
}