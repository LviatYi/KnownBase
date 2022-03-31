#include "AvlTree.h"

int main() {
    AvlTree tree;

    vector<int> input = { 93,76,74,83,79,52,56,10,8,26,98,97,9,16,23,37,41,27,60,66,42,44,30,34,63,14,99,39,71,57 };
    tree.insert(input);
    tree.show(tree.inorderWalk());
    tree.drop(52).drop(60).drop(27).drop(83).drop(93).drop(79).drop(98).drop(97);
    tree.show(tree.inorderWalk());

    return 1;
}