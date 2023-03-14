#pragma once
#include <map>
#include <unordered_set>

class Solution729 {
private:
    std::map<int, int> calendar_;
    /// <summary>
    /// tree_ 表示区间 [l,r] 是否存在标记为 1 的元素
    /// lazy_ 表示区间 [l,r] 全为标记为 1 的元素
    /// </summary>
    std::unordered_set<int> tree_, lazy_;

    bool query(int start, int end, int l, int r, int idx);

    void update(int start, int end, int l, int r, int idx);

public:
    Solution729();

    bool book(int start, int end);

    bool book2(int start, int end);
};
