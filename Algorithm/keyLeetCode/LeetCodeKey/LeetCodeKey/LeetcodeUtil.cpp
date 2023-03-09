#include "LeetcodeUtil.h"

std::vector<std::vector<int>> LeetcodeUtil::deserialize_vector_vector(std::string in) {
    std::vector<std::vector<int>> ret = {};

    if (in.empty()) {
        return ret;
    }

    in.erase(std::remove_if(in.begin(), in.end(), isspace), in.end());

    int squareBracketCount = 0;

    bool element_valid = false;
    bool vector_valid = false;
    int number = 0;
    std::vector<int> current_vector = std::vector<int>();


    for (int i = 0; i < in.size(); ++i) {
        if (in[i] == '[') {
            element_valid = true;
            vector_valid = true;
            --squareBracketCount;
        }
        else if (std::isdigit(in[i])) {
            number *= 10;
            number += in[i] - '0';
        }

        else if (in[i] == ',' || in[i] == ']') {
            if (element_valid) {
                current_vector.push_back(number);
                number = 0;
            }

            if (in[i] == ']') {
                --squareBracketCount;
                if (vector_valid) {
                    ret.push_back(current_vector);
                    current_vector.clear();
                }
                element_valid = false;
                vector_valid = false;
            }
        }
    }

    if (~squareBracketCount) {
        return ret;
    }
    return {};
}

static void subDeserialize(std::vector<std::string>& datas, int& i, TreeNode* root) {
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

TreeNode* LeetcodeUtil::deserialize_tree_node(std::string data) {
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

static void subSerialize(TreeNode* root, std::string& ans) {
    if (!root) {
        ans.append("null,");
        return;
    }
    ans.append(std::to_string(root->val) + ",");

    subSerialize(root->left, ans);
    subSerialize(root->right, ans);
}

std::string LeetcodeUtil::serialize_tree_node(TreeNode* root) {
    std::string ans;
    subSerialize(root, ans);

    return ans;
}
