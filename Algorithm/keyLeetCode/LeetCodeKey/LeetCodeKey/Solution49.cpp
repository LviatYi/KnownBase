#include "Solution49.h"

#include <algorithm>
#include <unordered_map>

std::vector<std::vector<std::string>> Solution49::groupAnagrams(std::vector<std::string>& strs) {
    std::unordered_map<std::string, std::vector<std::string>> mp;
    for (std::string& str : strs) {
        std::string key = str;
        sort(key.begin(), key.end());
        mp[key].emplace_back(str);
    }
    std::vector<std::vector<std::string>> ans;
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        ans.emplace_back(it->second);
    }
    return ans;
}
