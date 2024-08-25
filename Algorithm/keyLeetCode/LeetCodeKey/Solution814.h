#pragma once
#include "TreeNode.h"

class Solution814 {
private:
    bool needCutSub(TreeNode* sub);

public:
    TreeNode* pruneTree(TreeNode* root);
};
