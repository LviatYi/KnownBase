#include "Swordii52.h"

std::pair<TreeNode*, TreeNode*> Swordii52::sub_increasing_bst(TreeNode* root) {
        if (!root) {
            return {nullptr, nullptr};
        }

        auto left = sub_increasing_bst(root->left);
        auto right = sub_increasing_bst(root->right);

        root->left = nullptr;
        if (left.second) {
            left.second->right = root;
        }

        root->right = right.first;

        return {left.first != nullptr ? left.first : root, right.second != nullptr ? right.second : root};
}

TreeNode* Swordii52::increasingBST(TreeNode* root) {
    return sub_increasing_bst(root).first;
}
