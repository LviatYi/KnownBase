#include "Solution101.h"

static bool isSame(Swordii43TreeNode* r1, Swordii43TreeNode* r2) {
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

static bool isSubSymmetric(Swordii43TreeNode* a, Swordii43TreeNode* b) {
    if (!a && !b) {
        return true;
    }

    return isSame(a, b) && isSubSymmetric(a->left, b->right) && isSubSymmetric(a->right, b->left);
}


bool Solution101::isSymmetric(Swordii43TreeNode* root) {
    return isSubSymmetric(root, root);
}
