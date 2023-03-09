#pragma once
#include <utility>

#include "TreeNode.h"

class Swordii45 {
private:
    std::pair<TreeNode*, int> dfs(TreeNode* root, int depth);
public:
    int findBottomLeftValue(TreeNode* root);
    int findBottomLeftValue2(TreeNode* root);
};
