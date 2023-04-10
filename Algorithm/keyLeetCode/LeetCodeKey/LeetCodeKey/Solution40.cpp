#include "Solution40.h"
#include<algorithm>
using namespace std;

static vector<int> currentAns;

static void dfs(vector<int>& candidates, vector<vector<int>>& ans, int start, int target) {
    if (target < 0) return;
    if (target == 0) {
        ans.push_back(currentAns);
        return;
    }
    for (int i = start; i < candidates.size(); i++) {
        if (candidates[i] <= target) {
            if (i != start && candidates[i] == candidates[i - 1]) {
                continue;
            }
            currentAns.push_back(candidates[i]);
            dfs(candidates, ans, i + 1, target - candidates[i]);
            currentAns.pop_back();
        }
    }
}

vector<vector<int>> Solution40::combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> ans;
    dfs(candidates, ans, 0, target);
    return ans;
}
