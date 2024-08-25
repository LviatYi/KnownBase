#pragma once
#include <map>
#include <vector>

class Swordii82 {
private:
    std::vector<int> t = {};
    std::vector<std::vector<int>> ret = {};

    void dfs(std::map<int, int>& map, std::map<int, int>::iterator p, int target);

public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target);
};
