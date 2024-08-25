#include "Swordii49.h"

void Swordii49::dfs(TreeNode* root, int current_sum, int* sum) {
    if (!root) {
        return;
    }

    current_sum *= 10;
    current_sum += root->val;

    if (!root->left && !root->right) {
        *sum = *sum + current_sum;
        return;
    }

    dfs(root->left, current_sum, sum);
    dfs(root->right, current_sum, sum);
}

int Swordii49::sumNumbers(TreeNode* root) {
    if (!root) {
        return 0;
    }
    int* sum = new int(0);
    dfs(root, 0, sum);

    return *sum;
}
