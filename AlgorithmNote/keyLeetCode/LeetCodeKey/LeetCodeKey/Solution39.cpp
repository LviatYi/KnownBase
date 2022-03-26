#include "Solution39.h"
#include<algorithm>

using namespace std;

static vector<int>currentAns;

#pragma region 回溯
/// <summary>
/// 
/// </summary>
/// <param name="candidates"></param>
/// <param name="ans"></param>
/// <param name="start">起始可选的数字 index</param>
/// <param name="target"></param>
static void dfs(vector<int>& candidates, vector<vector<int>>& ans, int start, int target) {
    if (target < 0) return;
    if (target == 0) {
        ans.push_back(currentAns);
        return;
    }
    for (int i = start; i < candidates.size(); i++) {
        if (candidates[i] <= target) {
            currentAns.push_back(candidates[i]);
            dfs(candidates, ans, i, target - candidates[i]);
            currentAns.pop_back();
        }
    }
}

vector<vector<int>> Solution39::combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>>ans;
    dfs(candidates, ans, 0, target);
    return ans;
}
#pragma endregion