#pragma once
#include <string>
#include <vector>

#include "TreeNode.h"

class Swordii48 {
public:
    void subSerialize(TreeNode* root, std::vector<std::string>& ans);

    void subDeserialize(std::vector<std::string>& datas, int& i, TreeNode* root);

    std::string serialize(TreeNode* root, bool zip = false);

    TreeNode* deserialize(std::string data);
    // Your Codec object will be instantiated and called as such:
    // Codec codec;
    // codec.deserialize(codec.serialize(root));
};
