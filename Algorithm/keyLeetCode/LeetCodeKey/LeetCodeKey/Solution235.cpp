#include "Solution235.h"

#pragma region 模拟
Swordii43TreeNode* Solution235::lowestCommonAncestor(Swordii43TreeNode* root, Swordii43TreeNode* p,
                                                     Swordii43TreeNode* q) {
    Swordii43TreeNode* ans = root;

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
