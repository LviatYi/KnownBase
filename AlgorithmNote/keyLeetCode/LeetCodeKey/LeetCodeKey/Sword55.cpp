#include "Sword55.h"

int Sword55::maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        int left = maxDepth(root->left) + 1;
        int right = maxDepth(root->right) + 1;

        if (left > right) {
            return left;
        }
        else {
            return right;
        }
}