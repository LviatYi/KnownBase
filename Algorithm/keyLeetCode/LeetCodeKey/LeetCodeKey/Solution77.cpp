#include "Solution77.h"

void Solution77::dfs(int index, int n, int k) {
    if (index > n) {
        return;
    }
    if (n - index < k - t.size() - 1) {
        return;
    }
    t.push_back(index);
    if (t.size() == k) {
        ret.push_back(t);
    }
    else {
        dfs(index + 1, n, k);
    }
    t.pop_back();
    dfs(index + 1, n, k);
}

std::vector<std::vector<int>> Solution77::combine(int n, int k) {
    dfs(1, n, k);

    return ret;
}
