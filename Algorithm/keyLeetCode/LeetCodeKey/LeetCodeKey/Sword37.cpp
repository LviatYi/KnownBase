#include "Sword37.h"
#include<vector>
using std::vector;
using std::to_string;

    static void subSerialize(TreeNode* root, string& ans) {
        if (!root) {
            ans.append("null,");
            return;
        }
        ans.append(to_string(root->val) + ",");

        subSerialize(root->left, ans);
        subSerialize(root->right, ans);
    }

    string Sword37::serialize(TreeNode* root) {
        string ans;
        subSerialize(root, ans);

        return ans;
    }

    static void subDeserialize(vector<string>& datas, int& i, TreeNode* root) {
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

    TreeNode* Sword37::deserialize(string data) {
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
        TreeNode* root = new TreeNode(std::stoi(datas.at(i++)));
        subDeserialize(datas, i, root);
        return root;
    }