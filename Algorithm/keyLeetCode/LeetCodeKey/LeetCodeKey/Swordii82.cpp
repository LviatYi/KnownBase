#include "Swordii82.h"

void Swordii82::dfs(std::map<int, int>& map, std::map<int, int>::iterator p, int target) {
    if (target == 0) {
        ret.push_back(t);
        return;
    }
    if (target < 0 || p == map.end()) {
        return;
    }

    int i = 0;
    for (; i <= p->second; ++i) {
        const int new_target = target - p->first * i;
        if (new_target > 0) {
            if (i > 0) {
                t.emplace_back(p->first);
            }
            dfs(map, std::next(p, 1), new_target);
        }
        else {
            break;
        }
    }
    while (--i) {
        t.pop_back();
    }
}

std::vector<std::vector<int>> Swordii82::combinationSum2(std::vector<int>& candidates, int target) {
    std::map<int, int> map = {};

    for (auto candidate : candidates) {
        if (map.count(candidate)) {
            ++map[candidate];
        }
        else {
            map[candidate] = 1;
        }
    }

    dfs(map, map.begin(), target);

    return ret;
}
