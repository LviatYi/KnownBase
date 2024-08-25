#include "Solution236.h"

static bool dfs(TreeNode* root, int p, int q, TreeNode*& ans) {
    if (!root) {
        return false;
    }

    bool left = dfs(root->left, p, q, ans);
    bool right = dfs(root->right, p, q, ans);

    if (!ans && (left && right || ((left || right) && (root->val == p || root->val == q)))) {
        ans = root;
        return true;
    }
    else {
        return left || right || root->val == p || root->val == q;
    }
}

TreeNode* Solution236::lowestCommonAncestor(TreeNode* root, TreeNode* p,
                                            TreeNode* q) {
    TreeNode* ans = nullptr;

    dfs(root, p->val, q->val, ans);

    return ans;
}
