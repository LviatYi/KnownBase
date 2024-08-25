#pragma once
#include <vector>

#include "TreeNode.h"

class Swordii46 {
private:
    void dfs(TreeNode* root, std::vector<int>& ret, int depth);
public:
    std::vector<int> rightSideView(TreeNode* root);
    std::vector<int> rightSideView2(TreeNode* root);
};
