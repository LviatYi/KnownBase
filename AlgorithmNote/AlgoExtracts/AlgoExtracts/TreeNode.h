#pragma once

struct TreeNode {
    int key = 0;
    int bf = 0;
    TreeNode* p = nullptr;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    TreeNode(int _key) :key(_key) {};
    TreeNode(int _key, TreeNode* _p) :key(_key), p(_p) {};
};