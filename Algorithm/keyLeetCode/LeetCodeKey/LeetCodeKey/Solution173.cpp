#include "Solution173.h"

Solution173::Solution173(TreeNode* root) {
    if (!root) {
        return;
    }

    TreeNode* current = root;
    std::stack<TreeNode*> helper;

    while (current || !helper.empty()) {
        while (current) {
            helper.push(current);
            current = current->right;
        }

        current = helper.top();
        helper.pop();
        stack_.push(current);
        current = current->left;
    }
}

int Solution173::next() {
    int ret = stack_.top()->val;
    stack_.pop();
    return ret;
}

bool Solution173::hasNext() {
    return !stack_.empty();
}
