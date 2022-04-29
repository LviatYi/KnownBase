#pragma once
#include<string>
#include"TreeNode.h"

using std::string;
class Sword37 {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root);

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data);
};