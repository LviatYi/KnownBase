#include "Swordii50.h"

#include <queue>

int Swordii50::dfs(TreeNode* root, long long curr, int targetSum) {
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


int Swordii50::pathSum(TreeNode* root, int targetSum) {
    prefix[0] = 1;
    return dfs(root, 0, targetSum);
}
