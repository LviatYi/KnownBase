#pragma once
#include <string>
#include <vector>

#include "TreeNode.h"

class LeetcodeUtil {
public:
    static std::vector<std::vector<int>> deserialize_vector_vector(std::string in);
    static TreeNode* deserialize_tree_node(std::string data);
    static std::string serialize_tree_node(TreeNode* root);
};
