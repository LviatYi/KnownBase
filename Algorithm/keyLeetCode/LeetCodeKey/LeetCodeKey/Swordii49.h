#pragma once
#include "TreeNode.h"

class Swordii49 {
private:
    void dfs(TreeNode* root, int current_sum, int* sum);
public:
    int sumNumbers(TreeNode* root);
};
