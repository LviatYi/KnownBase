#pragma once

struct Swordii43TreeNode {
    int val;
    Swordii43TreeNode* left;
    Swordii43TreeNode* right;

    Swordii43TreeNode() : val(0), left(nullptr), right(nullptr) {
    }

    Swordii43TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }

    Swordii43TreeNode(int x, Swordii43TreeNode* left, Swordii43TreeNode* right) : val(x), left(left), right(right) {
    }
};

class Swordii43 {
private:
    int cnt_ = 0;
    Swordii43TreeNode* root_;
public:
    Swordii43(Swordii43TreeNode* root);
    int insert(int v);
    Swordii43TreeNode* get_root();
};
