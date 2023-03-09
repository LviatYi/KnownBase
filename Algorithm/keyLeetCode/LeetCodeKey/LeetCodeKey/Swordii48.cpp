#include "Swordii48.h"

void Swordii48::subSerialize(TreeNode* root, std::string& ans) {
    if (!root) {
        ans.append("null,");
        return;
    }
    ans.append(std::to_string(root->val) + ",");

    subSerialize(root->left, ans);
    subSerialize(root->right, ans);
}

void Swordii48::subDeserialize(std::vector<std::string>& datas, int& i, TreeNode* root) {
    if (datas.at(i) == "null") {
        i++;
        root->left = nullptr;
    }
    else {
        root->left = new TreeNode(std::stoi(datas.at(i)));
        i++;
        subDeserialize(datas, i, root->left);
    }
    if (datas.at(i) == "null") {
        i++;
        root->right = nullptr;
    }
    else {
        root->right = new TreeNode(std::stoi(datas.at(i)));
        i++;
        subDeserialize(datas, i, root->right);
    }
    return;
}

std::string Swordii48::serialize(TreeNode* root) {
    std::string ans;
    subSerialize(root, ans);

    return ans;
}

TreeNode* Swordii48::deserialize(std::string data) {
    std::vector<std::string> datas;
    std::string word;
    for (char c : data) {
        if (c != ',') {
            word += c;
        }
        else {
            datas.push_back(word);
            word.clear();
        }
    }

    if (datas.empty() || datas.at(0) == "null") {
        return nullptr;
    }
    int i = 0;
    TreeNode* root = new TreeNode(std::stoi(datas.at(i++)));
    subDeserialize(datas, i, root);
    return root;
}
