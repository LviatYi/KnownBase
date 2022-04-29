#pragma once
#include "TreeNode.h"
#include <vector>

using std::vector;
class AvlTree {
private:
    TreeNode* head = nullptr;

    TreeNode* find(int key, TreeNode* subTree);
    TreeNode* findMin(TreeNode* subTree);
    TreeNode* findMax(TreeNode* subTree);
    void transplant(TreeNode* u, TreeNode* v);
    void Lrotate(TreeNode* subTree);
    void Rrotate(TreeNode* subTree);
    void LRrotate(TreeNode* subTree);
    void RLrotate(TreeNode* subTree);
    vector<int> inorderWalk(TreeNode* subTree, vector<int>& nums);
    TreeNode* insert(TreeNode* _n);
public:
    TreeNode* find(int key);
    TreeNode* findMin();
    TreeNode* findMax();

    AvlTree& insert(int key);
    AvlTree& insert(vector<int> keys);
    AvlTree& drop(int key);
    vector<int> inorderWalk();
    void show(const vector<int>& nums);
};

