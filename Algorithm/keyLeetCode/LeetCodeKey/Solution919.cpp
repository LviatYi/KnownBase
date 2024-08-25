#include "Solution919.h"
#include <immintrin.h>
#include <queue>

Solution919::Solution919(Solution919TreeNode* root) {
    this->root_ = root;

    std::queue<Solution919TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        ++cnt_;
        Solution919TreeNode* node = q.front();
        q.pop();
        if (node->left) {
            q.push(node->left);
        }
        if (node->right) {
            q.push(node->right);
        }
    }
}

int Solution919::insert(int v) {
    ++cnt_;
    Solution919TreeNode* child = new Solution919TreeNode(v);
    Solution919TreeNode* node = root_;
    // in gcc
    //int highbit = 31 - __builtin_clz(cnt);
    // in msvc
    int highbit = 31 - _lzcnt_u64(cnt_);
    for (int i = highbit - 1; i >= 1; --i) {
        if (cnt_ & (1 << i)) {
            node = node->right;
        }
        else {
            node = node->left;
        }
    }
    if (cnt_ & 1) {
        node->right = child;
    }
    else {
        node->left = child;
    }
    return node->val;
}

Solution919TreeNode* Solution919::get_root() {
    return root_;
}
