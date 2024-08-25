#include "Swordii44.h"

#include <queue>

#pragma region DFS
void Swordii44::dfs(TreeNode* root, std::vector<int>& ret, int depth) {
    if (depth + 1 > ret.size()) {
        ret.push_back(root->val);
    }
    else {
        ret[depth] = std::max(ret[depth], root->val);
    }

    if (root->left) {
        dfs(root->left, ret, depth + 1);
    }
    if (root->right) {
        dfs(root->right, ret, depth + 1);
    }
}


std::vector<int> Swordii44::largestValues3(TreeNode* root) {
    if (!root) {
        return {};
    }
    std::vector<int> ret;
    dfs(root, ret, 0);

    return ret;
}

#pragma endregion

#pragma region BFS

#pragma region 辅助栈
std::vector<int> Swordii44::largestValues(TreeNode* root) {
    if (root == nullptr) {
        return {};
    }

    std::queue<TreeNode*> q1;
    std::queue<TreeNode*> q2;
    q1.push(root);
    auto active_queue = &q1;
    auto inactive_queue = &q2;

    std::vector<int> max_values = {};

    int current_max_value = INT_MIN;

    while (!q1.empty() || !q2.empty()) {
        TreeNode* current_tree_node = active_queue->front();
        active_queue->pop();
        if (current_tree_node->left) {
            inactive_queue->push(current_tree_node->left);
        }
        if (current_tree_node->right) {
            inactive_queue->push(current_tree_node->right);
        }

        current_max_value = current_max_value > current_tree_node->val ? current_max_value : current_tree_node->val;

        if (active_queue->empty()) {
            max_values.push_back(current_max_value);
            current_max_value = INT_MIN;
            std::swap(active_queue, inactive_queue);
        }
    }

    return max_values;
}
#pragma endregion

#pragma region 单栈
std::vector<int> Swordii44::largestValues2(TreeNode* root) {
    std::vector<int> ans;
    if (root == nullptr) return ans;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int cursize = q.size();
        int tmp = INT_MIN;
        while (cursize) {
            TreeNode* curtop = q.front();
            tmp = std::max(curtop->val, tmp);
            q.pop();
            cursize--;
            if (curtop->left) q.push(curtop->left);
            if (curtop->right) q.push(curtop->right);
        }
        ans.push_back(tmp);
    }
    return ans;
}
#pragma endregion

#pragma endregion
