#pragma once
#include <unordered_map>

#include "TreeNode.h"

class Solution437 {
public:
    std::unordered_map<long long, int> prefix;

    int dfs(TreeNode* root, long long curr, int targetSum);

    int pathSum(TreeNode* root, int targetSum);
};
