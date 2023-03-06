#include "Solution236.h"

static bool dfs(Swordii43TreeNode* root, int p, int q, Swordii43TreeNode*& ans) {
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

Swordii43TreeNode* Solution236::lowestCommonAncestor(Swordii43TreeNode* root, Swordii43TreeNode* p,
                                                     Swordii43TreeNode* q) {
    Swordii43TreeNode* ans = nullptr;

    dfs(root, p->val, q->val, ans);

    return ans;
}
