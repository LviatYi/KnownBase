#include "Sword34.h"

static void subPathSum(TreeNode* root, int target, vector<int>& currentAns, vector<vector<int>>& ans) {
    if (target < 0) {
        return;
    }

    if (root->left) {
        currentAns.push_back(root->left->val);
        subPathSum(root->left, target - root->left->val, currentAns, ans);
        currentAns.pop_back();
    }
    if (root->right) {
        currentAns.push_back(root->right->val);
        subPathSum(root->right, target - root->right->val, currentAns, ans);
        currentAns.pop_back();
    }

    if (!root->left && !root->right && target == 0) {
        ans.push_back(currentAns);
    }
}

vector<vector<int>> Sword34::pathSum(TreeNode* root, int target) {
    vector<vector<int>> ans;

    if (!root) {
        return ans;
    }
    vector<int>currentAns(root->val);
    subPathSum(root, target - root->val, currentAns, ans);

    return ans;
}