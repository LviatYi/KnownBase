#include "Swordii53.h"

TreeNode* Swordii53::inorderSuccessor(TreeNode* root, TreeNode* p) {
    TreeNode* current;

    if (p->right) {
        current = p->right;
        while (current->left) {
            current = current->left;
        }
        return current;
    }

    TreeNode* last_current = nullptr;
    current = root;
    while (p->val != current->val) {
        if (p->val < current->val) {
            last_current = current;
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    return last_current;
}
