#include "Solution199.h"

#include <queue>

#pragma region BFS

std::vector<int> Solution199::rightSideView(TreeNode* root) {
    if (!root) {
        return {};
    }
    std::queue<TreeNode*> queue;
    queue.push(root);
    std::vector<int> ret = {};

    while (!queue.empty()) {
        int n = queue.size();
        while (n--) {
            if (n == 0) {
                ret.push_back(queue.front()->val);
            }
            if (queue.front()->left) {
                queue.push(queue.front()->left);
            }
            if (queue.front()->right) {
                queue.push(queue.front()->right);
            }
            queue.pop();
        }
    }

    return ret;
}

#pragma endregion

#pragma region DFS

void Solution199::dfs(TreeNode* root, std::vector<int>& ret, int depth) {
    if (depth >= ret.size()) {
        ret.push_back(root->val);
    }
    else {
        ret[depth] = root->val;
    }

    if (root->left) {
        dfs(root->left, ret, depth + 1);
    }
    if (root->right) {
        dfs(root->right, ret, depth + 1);
    }
}

std::vector<int> Solution199::rightSideView2(TreeNode* root) {
    if (!root) {
        return {};
    }

    std::vector<int> ret;
    dfs(root, ret, 0);
    return ret;
}
#pragma endregion
