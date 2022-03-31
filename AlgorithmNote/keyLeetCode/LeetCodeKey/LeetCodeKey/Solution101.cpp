#include "Solution101.h"

bool isSame(TreeNode* r1, TreeNode* r2) {
    if (!r1 && !r2) {
        return true;
    }
    else if (r1 && r2) {
        return r1->val == r2->val;
    }
    else {
        return false;
    }
}

bool isSubSymmetric(TreeNode* a, TreeNode* b) {
    if (!a && !b) {
        return true;
    }

    return isSame(a, b) && isSubSymmetric(a->left, b->right) && isSubSymmetric(a->right, b->left);
}


bool Solution101::isSymmetric(TreeNode* root) {
    return isSubSymmetric(root, root);
}

