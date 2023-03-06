#pragma once


struct Solution919TreeNode {
    int val;
    Solution919TreeNode* left;
    Solution919TreeNode* right;

    Solution919TreeNode() : val(0), left(nullptr), right(nullptr) {
    }

    Solution919TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }

    Solution919TreeNode(int x, Solution919TreeNode* left,
                        Solution919TreeNode* right) : val(x), left(left), right(right) {
    }
};

class Solution919 {
private:
    int cnt_ = 0;
    Solution919TreeNode* root_;
public:
    Solution919(Solution919TreeNode* root);
    int insert(int v);
    Solution919TreeNode* get_root();
};
