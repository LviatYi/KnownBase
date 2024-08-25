#include "Solution235.h"

#pragma region 模拟
TreeNode* Solution235::lowestCommonAncestor(TreeNode* root, TreeNode* p,
                                            TreeNode* q) {
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
