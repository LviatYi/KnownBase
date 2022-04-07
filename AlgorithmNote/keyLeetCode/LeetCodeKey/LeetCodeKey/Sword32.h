#pragma once
#include"TreeNode.h"
#include<vector>

using std::vector;
class Sword32 {
public:
    vector<int> levelOrder(TreeNode* root);
    vector<vector<int>> levelOrder2(TreeNode* root);
    vector<vector<int>> levelOrder3(TreeNode* root);
};

