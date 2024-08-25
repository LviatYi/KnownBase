#include "Swordii33.h"

#include <algorithm>
#include <map>
#include <unordered_map>

std::vector<std::vector<std::string>> Swordii33::groupAnagrams(std::vector<std::string>& strs) {
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

#pragma region 没有意义的特征比较算法 也没有哈希 一坨 shit

bool operator==(const Swordii33::Anagram& lhs, const Swordii33::Anagram& rhs) {
    for (int i = 0; i < 26; ++i) {
        if (lhs.feature_[i] != rhs.feature_[i]) {
            return false;
        }
    }
    return true;
}

Swordii33::Anagram::Anagram(const std::string& str) {
    for (const char c : str) {
        ++feature_[c - 'a'];
    }
}


std::vector<std::vector<std::string>> Swordii33::groupAnagrams2(std::vector<std::string>& strs) {
    std::vector<Anagram> list = {};
    std::map<int, std::vector<std::string>> map = {};


    for (const auto& str : strs) {
        Anagram currentAnagram = Anagram(str);

        int list_index = -1;
        for (int i = 0; i < list.size(); ++i) {
            if (list[i] == currentAnagram) {
                list_index = i;
                break;
            }
        }

        if (list_index != -1) {
            map[list_index].push_back(str);
        }
        else {
            list_index = list.size();
            list.push_back(currentAnagram);
            map[list_index] = std::vector<std::string>{str};
        }
    }

    std::vector<std::vector<std::string>> ret = {};
    ret.reserve(map.size());
    for (const auto& pair : map) {
        ret.push_back(pair.second);
    }
    return ret;
}


#pragma endregion
