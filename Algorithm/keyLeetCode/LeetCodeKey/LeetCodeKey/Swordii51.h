#pragma once
#include <utility>

#include "TreeNode.h"

class Swordii51 {
private:
    int max_sum_ = INT_MIN;

    /**
     * \brief 给予一个节点，返回左侧及右侧的最大路径和  
     * \param root 根节点
     * \return 左侧及右侧的最大路径和
     */
    std::pair<int, int> maxSubPathSum(TreeNode* root);

    /**
     * \brief 给予一个节点，返回从此节点出发的最大向下路径和
     * \param root 根节点
     * \return 最大向下路径和
     */
    int maxSubPathSum2(TreeNode* root);
public:
    int maxPathSum(TreeNode* root);
};
