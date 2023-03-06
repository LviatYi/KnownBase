#include "Solution297.h"
#include<vector>
using std::vector;
using std::to_string;

static void subSerialize(Swordii43TreeNode* root, string& ans) {
    if (!root) {
        ans.append("null,");
        return;
    }
    ans.append(to_string(root->val) + ",");

    subSerialize(root->left, ans);
    subSerialize(root->right, ans);
}

string Solution297::serialize(Swordii43TreeNode* root) {
    string ans;
    subSerialize(root, ans);

    return ans;
}

static void subDeserialize(vector<string>& datas, int& i, Swordii43TreeNode* root) {
    if (datas.at(i) == "null") {
        i++;
        root->left = nullptr;
    }
    else {
        root->left = new Swordii43TreeNode(std::stoi(datas.at(i)));
        i++;
        subDeserialize(datas, i, root->left);
    }
    if (datas.at(i) == "null") {
        i++;
        root->right = nullptr;
    }
    else {
        root->right = new Swordii43TreeNode(std::stoi(datas.at(i)));
        i++;
        subDeserialize(datas, i, root->right);
    }
    return;
}

Swordii43TreeNode* Solution297::deserialize(string data) {
    vector<string> datas;
    string word;
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
    Swordii43TreeNode* root = new Swordii43TreeNode(std::stoi(datas.at(i++)));
    subDeserialize(datas, i, root);
    return root;
}
