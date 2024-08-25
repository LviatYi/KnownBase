#include "Swordii85.h"

void Swordii85::dfs(const int& n, int pre_count, int back_count) {
    if (temp.size() == 2 * n && pre_count == n) {
        ret.push_back(temp);
        return;
    }

    if (pre_count < n) {
        temp.push_back('(');
        dfs(n, pre_count + 1, back_count);
        temp.pop_back();
    }
    if (back_count < pre_count) {
        temp.push_back(')');
        dfs(n, pre_count, back_count + 1);
        temp.pop_back();
    }
}

std::vector<std::string> Swordii85::generateParenthesis(int n) {
    dfs(n, 0, 0);
    return ret;
}
