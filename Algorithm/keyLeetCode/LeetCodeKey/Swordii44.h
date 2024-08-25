#pragma once
#include <vector>

#include "TreeNode.h"

class Swordii44 {
private:
    void dfs(TreeNode* root, std::vector<int>& ret, int depth);
public:
    std::vector<int> largestValues(TreeNode* root);
    std::vector<int> largestValues2(TreeNode* root);
    std::vector<int> largestValues3(TreeNode* root);
};
