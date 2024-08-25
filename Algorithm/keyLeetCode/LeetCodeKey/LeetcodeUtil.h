#pragma once
#include <string>
#include <vector>

#include "ListNode.h"
#include "TreeNode.h"

class LeetcodeUtil {
public:
    /**
     * \brief 将字符串反序列化为二维 int 数组
     * \param in 字符串
     * \return 二维 int 数组 vector<vector<int>>
     */
    static std::vector<std::vector<int>> deserialize_vector_vector(std::string in);

    static ListNode* deserialize_list_node(std::string in);

    static std::vector<ListNode*> deserialize_vector_list_node(std::string in);

    /**
     * \brief 将字符串反序列化为二叉树，使用先序遍历顺序，且叶子节点的左右子节点为 nullptr\n
     *  ....1.....                                                \n
     *  ../...\...                                                \n
     *  .2.....3.. <==> "1,2,null,null,3,4,null,null,5,null,null" \n
     *  ....../.\.                                                \n
     *  .....4...5                                                \n
     * \param data 字符串
     * \return 二叉树根节点
     */
    static TreeNode* preorder_deserialize_tree_node(std::string data);

    /**
     * \brief 将二叉树序列化为字符串，使用先序遍历顺序，且叶子节点的左右子节点为 nullptr\n
     *  ....1.....                                                \n
     *  ../...\...                                                \n
     *  .2.....3.. <==> "1,2,null,null,3,4,null,null,5,null,null" \n
     *  ....../.\.                                                \n
     *  .....4...5                                                \n
     * \param root 二叉树根节点
     * \param zip 是否去除末尾的 null
     * \return 字符串
     */
    static std::string preorder_serialize_tree_node(TreeNode* root, bool zip = false);

    /**
     * \brief 将字符串反序列化为二叉树，使用层序遍历顺序，父子节点都为 nullptr 将被压缩\n
     *  ....1......                                             \n
     *  ../...\....                                             \n
     *  .2.....3... <==>  "1,2,3,null,null,4,5,null,null,null,6"\n
     *  ....../.\..                                             \n
     *  .....4...5.                                             \n
     *  ..........\                                             \n
     *  ..........6                                             \n
     * \param data 字符串
     * \return 二叉树根节点
     */
    static TreeNode* level_order_deserialize_tree_node(std::string data);

    /**
     * \brief 将字符串反序列化为二叉树，使用层序遍历顺序，父子节点都为 nullptr 将被压缩\n
     *  ....1......                                             \n
     *  ../...\....                                             \n
     *  .2.....3... <==>  "1,2,3,null,null,4,5,null,null,null,6"\n
     *  ....../.\..                                             \n
     *  .....4...5.                                             \n
     *  ..........\                                             \n
     *  ..........6                                             \n
     * \param root 二叉树根节点
     * \param zip 是否去除末尾的 null
     * \return 字符串
     */
    static std::string level_order_serialize_tree_node(TreeNode* root, bool zip = false);


    /**
     * \brief 将输入字符串按分隔符分隔为集合
     * \param str 输入字符串
     * \param delim 分隔符
     * \return 分隔后的字符串集合
     */
    static std::vector<std::string> string_split(const std::string& str, char delim);

};
