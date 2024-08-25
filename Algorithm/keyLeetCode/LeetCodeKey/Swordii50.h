#pragma once
#include <unordered_map>
#include <vector>

#include "TreeNode.h"

class Swordii50 {
private:
    std::unordered_map<long long, int> prefix;
    int dfs(TreeNode* root, long long curr, int targetSum);
public:
    int pathSum(TreeNode* root, int targetSum);
};
