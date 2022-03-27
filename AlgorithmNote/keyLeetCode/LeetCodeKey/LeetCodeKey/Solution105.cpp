#include "Solution105.h"

static TreeNode* buildSubTree(
    vector<int>::iterator preorderBegin, vector<int>::iterator preorderEnd, vector<int>::iterator inorderBegin, vector<int>::iterator inorderEnd) {
    TreeNode* ans = nullptr;
    if (preorderBegin < preorderEnd) {
        ans = new TreeNode(*preorderBegin);
        vector<int>::iterator rootPosInInorder = find(inorderBegin, inorderEnd, *preorderBegin);

        int lCount = rootPosInInorder - inorderBegin;

        ans->left = buildSubTree(preorderBegin + 1, preorderBegin + lCount + 1, inorderBegin, rootPosInInorder);
        ans->right = buildSubTree(preorderBegin + lCount + 1, preorderEnd, rootPosInInorder + 1, inorderEnd);
    }

    return ans;
}

TreeNode* Solution105::buildTree(vector<int>& preorder, vector<int>& inorder) {
    // 前序遍历的首个为根结点。
    TreeNode* ans = buildSubTree(
        preorder.begin(),
        preorder.end(),
        inorder.begin(),
        inorder.end()
    );

    return ans;
}
