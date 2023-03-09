#include "LeetcodeUtil.h"

#include <list>
#include <queue>

#pragma region Serialize

#pragma region vector vector int

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
    auto current_vector = std::vector<int>();

    for (const char i : in) {
        if (i == '[') {
            element_valid = true;
            vector_valid = true;
            --squareBracketCount;
        }
        else if (std::isdigit(i)) {
            number *= 10;
            number += i - '0';
        }

        else if (i == ',' || i == ']') {
            if (element_valid) {
                current_vector.push_back(number);
                number = 0;
            }

            if (i == ']') {
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

#pragma endregion

#pragma region treenode

static void sub_preorder_deserialize_tree_node(std::vector<std::string>& datas, int& i, TreeNode* root) {
    if (i >= datas.size() || datas.at(i) == "null") {
        i++;
        root->left = nullptr;
    }
    else {
        root->left = new TreeNode(std::stoi(datas.at(i)));
        i++;
        sub_preorder_deserialize_tree_node(datas, i, root->left);
    }
    if (i >= datas.size() || datas.at(i) == "null") {
        i++;
        root->right = nullptr;
    }
    else {
        root->right = new TreeNode(std::stoi(datas.at(i)));
        i++;
        sub_preorder_deserialize_tree_node(datas, i, root->right);
    }
}

TreeNode* LeetcodeUtil::preorder_deserialize_tree_node(std::string data) {
    std::vector<std::string> datas;
    std::string word;

    datas = LeetcodeUtil::string_split(data, ',');

    if (datas.empty() || datas.at(0) == "null") {
        return nullptr;
    }
    int i = 0;
    TreeNode* root = new TreeNode(std::stoi(datas.at(i++)));
    sub_preorder_deserialize_tree_node(datas, i, root);
    return root;
}

static void sub_preorder_serialize_tree_node(TreeNode* root, std::vector<std::string>& ans) {
    if (!root) {
        ans.push_back("null");
        return;
    }
    ans.push_back(std::to_string(root->val));

    sub_preorder_serialize_tree_node(root->left, ans);
    sub_preorder_serialize_tree_node(root->right, ans);
}

std::string LeetcodeUtil::preorder_serialize_tree_node(TreeNode* root, bool zip) {
    std::vector<std::string> words;
    sub_preorder_serialize_tree_node(root, words);

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

TreeNode* LeetcodeUtil::level_order_deserialize_tree_node(std::string data) {
    if (data.empty()) return nullptr;
    std::string str;
    std::vector<std::string> words = LeetcodeUtil::string_split(data, ',');
    int j = 0;

    std::queue<TreeNode*> queue;
    auto root = new TreeNode(std::stoi(words[j++]));
    queue.emplace(root);

    while (!queue.empty() && j < words.size()) {
        int size = queue.size();
        for (int i = 0; i < size && j < words.size(); ++i) {
            TreeNode* node = queue.front();
            queue.pop();

            if (node == nullptr) {
                j += 2;
            }

            else {
                if (words[j] != "null") {
                    auto left_child = new TreeNode(std::stoi(words[j]));
                    node->left = left_child;
                    queue.emplace(left_child);
                }
                else {
                    queue.emplace(nullptr);
                }
                ++j;
                if (words[j] != "null") {
                    auto right_child = new TreeNode(std::stoi(words[j]));
                    node->right = right_child;
                    queue.emplace(right_child);
                }
                else {
                    queue.emplace(nullptr);
                }
                ++j;
            }
        }
    }
    return root;
}

std::string LeetcodeUtil::level_order_serialize_tree_node(TreeNode* root, bool zip) {
    if (root == nullptr) return "null";

    std::vector<std::string> words;
    std::queue<TreeNode*> queue;
    queue.emplace(root);

    while (!queue.empty()) {
        int size = queue.size();
        for (int i = 0; i < size; ++i) {
            TreeNode* node = queue.front();
            queue.pop();
            if (node == nullptr) {
                words.emplace_back("null");
                queue.emplace(nullptr);
                queue.emplace(nullptr);

            }
            else {
                words.emplace_back(std::to_string(node->val));
                queue.emplace(node->left);
                queue.emplace(node->right);
            }
        }
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

#pragma endregion

#pragma endregion

#pragma region String

std::vector<std::string> LeetcodeUtil::string_split(const std::string& str, char delim) {
    std::size_t previous = 0;
    std::size_t current = str.find_first_of(delim);
    std::vector<std::string> elems;
    while (current != std::string::npos) {
        if (current > previous) {
            elems.push_back(str.substr(previous, current - previous));
        }
        previous = current + 1;
        current = str.find_first_of(delim, previous);
    }
    if (previous != str.size()) {
        elems.push_back(str.substr(previous));
    }
    return elems;
}

#pragma endregion
