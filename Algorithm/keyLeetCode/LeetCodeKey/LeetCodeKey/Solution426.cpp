#include "Solution426.h"

static Swordii43TreeNode* inorderWalk(Swordii43TreeNode* root, Swordii43TreeNode*& lastNode) {
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

Swordii43TreeNode* Solution426::treeToDoublyList(Swordii43TreeNode* root) {
    Swordii43TreeNode* preHead = new Swordii43TreeNode(0);
    Swordii43TreeNode* lastNode = preHead;

    Swordii43TreeNode* last = inorderWalk(root, lastNode);
    if (preHead->right) {
        last->right = preHead->right;
        preHead->right->left = last;
    }

    return preHead->right;
}
