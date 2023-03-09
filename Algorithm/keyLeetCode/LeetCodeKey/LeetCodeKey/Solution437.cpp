#include "Solution437.h"

int Solution437::dfs(TreeNode* root, long long curr, int targetSum) {
    if (!root) {
        return 0;
    }

    int ret = 0;
    curr += root->val;
    if (prefix.count(curr - targetSum)) {
        ret = prefix[curr - targetSum];
    }

    prefix[curr]++;
    ret += dfs(root->left, curr, targetSum);
    ret += dfs(root->right, curr, targetSum);
    prefix[curr]--;

    return ret;
}

int Solution437::pathSum(TreeNode* root, int targetSum) {
    prefix[0] = 1;
    return dfs(root, 0, targetSum);
}
