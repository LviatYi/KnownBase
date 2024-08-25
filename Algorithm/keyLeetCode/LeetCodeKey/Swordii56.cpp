#include "Swordii56.h"

#include <deque>
#include <stack>

bool Swordii56::findTarget(TreeNode* root, int k) {
    if (!root) {
        return false;
    }

    std::deque<TreeNode*> deque;
    std::stack<TreeNode*> helper;

    TreeNode* current = root;
    while (current || !helper.empty()) {
        while (current) {
            helper.push(current);
            current = current->left;
        }

        current = helper.top();
        helper.pop();
        deque.emplace_back(current);
        current = current->right;
    }

    TreeNode* front = deque.front();
    TreeNode* back = deque.back();

    while (front != back) {
        int current_sum = front->val + back->val;

        if (current_sum == k) {
            return true;
        }
        else if (current_sum < k) {
            deque.pop_front();
            front = deque.front();
        }
        else {
            deque.pop_back();
            back = deque.back();
        }
    }

    return false;
}
