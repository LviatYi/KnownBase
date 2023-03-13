#pragma once
#include <stack>

#include "TreeNode.h"

class Swordii55 {
private:
    std::stack<TreeNode*> stack_;
public:
    Swordii55(TreeNode* root);

    int next();

    bool hasNext();
};
