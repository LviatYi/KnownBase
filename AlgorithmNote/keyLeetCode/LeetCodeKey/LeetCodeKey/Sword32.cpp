#include "Sword32.h"
#include <queue>
using std::queue;

vector<int> Sword32::levelOrder(TreeNode* root) {
        vector<int>ans;
        if (!root) {
            return ans;
        }
        queue<TreeNode*> floorTreeNodes;

        floorTreeNodes.push(root);

        while (!floorTreeNodes.empty()) {
            TreeNode* currentTreeNode = floorTreeNodes.front();

            if (currentTreeNode->left) {
                floorTreeNodes.push(currentTreeNode->left);
            }
            if (currentTreeNode->right) {
                floorTreeNodes.push(currentTreeNode->right);
            }

            ans.push_back(currentTreeNode->val);
            floorTreeNodes.pop();
        }

        return ans;
}
