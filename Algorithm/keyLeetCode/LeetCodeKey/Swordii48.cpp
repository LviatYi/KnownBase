#include "Swordii48.h"

#include "LeetcodeUtil.h"

void Swordii48::subSerialize(TreeNode* root, std::vector<std::string>& ans) {
    if (!root) {
        ans.push_back("null");
        return;
    }
    ans.push_back(std::to_string(root->val));

    subSerialize(root->left, ans);
    subSerialize(root->right, ans);
}

std::string Swordii48::serialize(TreeNode* root, bool zip) {
    std::vector<std::string> words;
    subSerialize(root, words);

    if (words.empty()) {
        return "null";
    }

    if (zip) {
        int r = words.size() - 1;
        while (words[r--] == "null") {
            words.pop_back();
        }
    }

    std::string ans = words[0];

    for (int i = 1; i < words.size(); ++i) {
        ans.append(",").append(words[i]);
    }

    return ans;
}

void Swordii48::subDeserialize(std::vector<std::string>& datas, int& i, TreeNode* root) {
    if (i >= datas.size() || datas.at(i) == "null") {
        i++;
        root->left = nullptr;
    }
    else {
        root->left = new TreeNode(std::stoi(datas.at(i)));
        i++;
        subDeserialize(datas, i, root->left);
    }
    if (i >= datas.size() || datas.at(i) == "null") {
        i++;
        root->right = nullptr;
    }
    else {
        root->right = new TreeNode(std::stoi(datas.at(i)));
        i++;
        subDeserialize(datas, i, root->right);
    }
}

TreeNode* Swordii48::deserialize(std::string data) {
    std::vector<std::string> datas;
    std::string word;

    datas = LeetcodeUtil::string_split(data, ',');

    if (datas.empty() || datas.at(0) == "null") {
        return nullptr;
    }
    int i = 0;
    TreeNode* root = new TreeNode(std::stoi(datas.at(i++)));
    subDeserialize(datas, i, root);
    return root;
}
