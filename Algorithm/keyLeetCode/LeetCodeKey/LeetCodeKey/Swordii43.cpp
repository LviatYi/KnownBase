#include "Swordii43.h"

#include <immintrin.h>
#include <queue>

Swordii43::Swordii43(Swordii43TreeNode* root) {
    this->root_ = root;

    std::queue<Swordii43TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        ++cnt_;
        Swordii43TreeNode* node = q.front();
        q.pop();
        if (node->left) {
            q.push(node->left);
        }
        if (node->right) {
            q.push(node->right);
        }
    }
}

int Swordii43::insert(int v) {
    ++cnt_;
    Swordii43TreeNode* child = new Swordii43TreeNode(v);
    Swordii43TreeNode* node = root_;
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

Swordii43TreeNode* Swordii43::get_root() {
    return root_;
}
