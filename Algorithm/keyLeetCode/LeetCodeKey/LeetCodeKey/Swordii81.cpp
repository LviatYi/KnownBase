#include "Swordii81.h"

void Swordii81::dfs(std::vector<int>& candidates, int target, int min_index) {
    if (target < 0) {
        return;
    }
    if (target == 0) {
        ret.push_back(t);
        return;
    }

    for (int i = min_index; i < candidates.size(); ++i) {
        t.push_back(candidates[i]);
        dfs(candidates, target - candidates[i], i);
        t.pop_back();
    }
}

std::vector<std::vector<int>> Swordii81::combinationSum(std::vector<int>& candidates, int target) {
    dfs(candidates, target, 0);
    return ret;
}
