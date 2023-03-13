#include "Swordii55.h"

Swordii55::Swordii55(TreeNode* root) {
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

int Swordii55::next() {
    int ret = stack_.top()->val;
    stack_.pop();
    return ret;
}

bool Swordii55::hasNext() {
    return !stack_.empty();
}
