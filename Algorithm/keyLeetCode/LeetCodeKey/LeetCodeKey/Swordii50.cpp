#include "Swordii50.h"

int Swordii50::pathSum(TreeNode* root, int targetSum) {
    if (!root) {
        return 0;
    }
    return (targetSum == root->val) + pathSum(root->left, targetSum - root->val) + pathSum(
        root->right, targetSum - root->val) + pathSum(root->left, targetSum) + pathSum(root->right, targetSum);
}
