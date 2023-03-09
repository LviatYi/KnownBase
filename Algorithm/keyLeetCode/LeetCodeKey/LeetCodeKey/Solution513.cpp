#include "Solution513.h"

#include <queue>

#pragma region BFS

int Solution513::findBottomLeftValue(TreeNode* root) {
    if (!root) {
        return -1;
    }

    std::queue<TreeNode*> queue;
    queue.push(root);
    TreeNode* ret = root;

    while (!queue.empty()) {
        int n = queue.size();
        while (n--) {
            if (queue.front()->left) {
                queue.push(queue.front()->left);
            }
            if (queue.front()->right) {
                queue.push(queue.front()->right);
            }
            queue.pop();
        }
        if (!queue.empty()) {
            ret = queue.front();
        }
    }
    return ret->val;
}

#pragma endregion

#pragma region DFS

std::pair<TreeNode*, int> Solution513::dfs(TreeNode* root, int depth) {
    int max_depth = depth;
    TreeNode* ret = root;

    if (root->left) {
        auto left_ret = dfs(root->left, depth + 1);
        if (max_depth < left_ret.second) {
            ret = left_ret.first;
            max_depth = left_ret.second;
        }
    }

    if (root->right) {
        auto right_ret = dfs(root->right, depth + 1);
        if (max_depth < right_ret.second) {
            ret = right_ret.first;
            max_depth = right_ret.second;
        }
    }

    return {ret, max_depth};
}

int Solution513::findBottomLeftValue2(TreeNode* root) {
    if (!root) {
        return -1;
    }
    return dfs(root, 0).first->val;
}

#pragma endregion
