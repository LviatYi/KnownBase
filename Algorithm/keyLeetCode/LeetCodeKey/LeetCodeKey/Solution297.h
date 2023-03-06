#pragma once
#include<string>
#include"Swordii43TreeNode.h"

using std::string;

class Solution297 {
public:
    // Encodes a tree to a single string.
    string serialize(Swordii43TreeNode* root);

    // Decodes your encoded data to tree.
    Swordii43TreeNode* deserialize(string data);
};
