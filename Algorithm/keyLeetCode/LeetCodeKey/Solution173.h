#pragma once
#include <stack>

#include "TreeNode.h"

class Solution173 {
private:
    std::stack<TreeNode*> stack_;
public:
    Solution173(TreeNode* root);

    int next();

    bool hasNext();
};
