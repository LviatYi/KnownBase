#include "Swordii51.h"

#include <algorithm>

std::pair<int, int> Swordii51::maxSubPathSum(TreeNode* root) {
    if (!root) {
        return {0, 0};
    }

    int left = 0;
    int right = 0;

    if (root->left) {
        const auto left_ret = maxSubPathSum(root->left);
        left = std::max({left_ret.first, left_ret.second, 0}) + root->left->val;
    }
    if (root->right) {
        const auto right_ret = maxSubPathSum(root->right);
        right = std::max({right_ret.first, right_ret.second, 0}) + root->right->val;
    }

    max_sum_ = std::max({max_sum_, left + right + root->val, left + root->val, right + root->val, root->val});

    return {left, right};
}

int Swordii51::maxSubPathSum2(TreeNode* root) {
    if (!root) {
        return 0;
    }

    int left = std::max(maxSubPathSum2(root->left), 0);
    int right = std::max(maxSubPathSum2(root->right), 0);

    max_sum_ = std::max(max_sum_, left + right + root->val);

    return std::max(left, right) + root->val;
}

int Swordii51::maxPathSum(TreeNode* root) {
    max_sum_ = INT_MIN;
    maxSubPathSum(root);
    return max_sum_;
}
