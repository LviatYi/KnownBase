#pragma once
#include <utility>

#include "TreeNode.h"

class Swordii52 {
private:
    static std::pair<TreeNode*, TreeNode*> sub_increasing_bst(TreeNode* root);
public:
    static TreeNode* increasingBST(TreeNode* root);
};
