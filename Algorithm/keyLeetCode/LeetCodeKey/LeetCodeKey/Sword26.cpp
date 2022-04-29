#include "Sword26.h"

static bool isSame(TreeNode* A, TreeNode* B) {
    if (B == nullptr) {
        return true;
    }
    else if (A == nullptr) {
        return false;
    }

    if (A->val != B->val) {
        return false;
    }

    return isSame(A->left, B->left) && isSame(A->right, B->right);
}

bool Sword26::isSubStructure(TreeNode* A, TreeNode* B) {
    if (!A || !B) {
        return false;
    }

    return isSame(A, B) || isSubStructure(A->left, B) || isSubStructure(A->right, B);
}