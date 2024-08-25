#include "Sword68.h"


#pragma region Sword68_1
TreeNode* Sword68::lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* ans = root;

    while (true) {
        if (p->val < ans->val && q->val < ans->val) {
            ans = ans->left;
        }
        else if (p->val > ans->val && q->val > ans->val) {
            ans = ans->right;
        }
        else {
            break;
        }
    }

    return ans;
}
#pragma endregion

#pragma region Sword68_2
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

TreeNode* Sword68::lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* ans = nullptr;

    dfs(root, p->val, q->val, ans);

    return ans;
}
#pragma endregion
