#include "Solution318.h"

#include <unordered_map>

#pragma region 位掩码
int Solution318::maxProduct(vector<string>& words) {
    vector<int> masks;
    for (string str : words) {
        int mask = 0;
        for (char c : str) {
            mask |= 1 << (c - 'a');
        }

        masks.push_back(mask);
    }

    int max_ret = 0;

    for (int i = 0; i < words.size(); ++i) {
        for (int j = i + 1; j < words.size(); ++j) {
            int curr_ret = words[i].size() * words[j].size();
            if (max_ret < curr_ret && !static_cast<bool>(masks[i] & masks[j])) {
                max_ret = curr_ret;
            }
        }
    }

    return max_ret;
}
#pragma endregion
#pragma region 位掩码 哈希表
int Solution318::maxProduct2(vector<string>& words) {
    unordered_map<int, int> masks;
    for (string str : words) {
        int mask = 0;
        for (char c : str) {
            mask |= 1 << (c - 'a');
        }
        if (masks.count(mask)) {
            if (masks.at(mask) < str.length()) {
                masks.at(mask) = str.length();
            }
        }
        else {
            masks.insert({mask, str.length()});
        }
    }

    int max_ret = 0;

    for (pair<const int, int> mask1 : masks) {
        for (pair<const int, int> mask2 : masks) {
            int curr_ret = mask1.second * mask2.second;
            if (!(mask1.first & mask2.first) && curr_ret > max_ret) {
                max_ret = curr_ret;
            }
        }
    }

    return max_ret;
}
#pragma endregion
