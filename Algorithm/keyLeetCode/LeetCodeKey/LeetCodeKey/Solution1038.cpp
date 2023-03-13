#include "Solution1038.h"

#include <stack>

TreeNode* Solution1038::bstToGst(TreeNode* root) {
    if (!root) {
        return root;
    }
    int sum = 0;

    std::stack<TreeNode*> helper_stack;

    TreeNode* current = root;

    while (current || !helper_stack.empty()) {
        while (current != nullptr) {
            helper_stack.push(current);
            current = current->right;
        }

        current = helper_stack.top();
        helper_stack.pop();

        sum += current->val;
        current->val = sum;
        current = current->left;
    }

    return root;
}
