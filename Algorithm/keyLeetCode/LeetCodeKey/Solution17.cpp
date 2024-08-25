#include "Solution17.h"
#include <unordered_map> 

using namespace std;

/// <summary>
/// 求笛卡尔乘积
/// </summary>
/// <param name="strs1"></param>
/// <param name="strs2"></param>
/// <returns></returns>
vector<string> Solution17::cartesian(vector<string> strs1, vector<string> strs2) {
    vector<string> ans;
    if (strs1.size() == 0) {
        return strs2;
    }
    else if (strs2.size() == 0) {
        return strs1;
    }

    for (string str1 : strs1) {
        for (string str2 : strs2) {
            ans.push_back(str1 + str2);
        }
    }

    return ans;
}

/// <summary>
/// 求笛卡尔乘积
/// </summary>
/// <param name="strs1"></param>
/// <param name="strs2"></param>
/// <returns></returns>
vector<string> Solution17::cartesian(vector<string> strs1, string str2) {
    vector<string>  strs2;
    for (char c : str2) {
        strs2.push_back(string(1, c));
    }

    return cartesian(strs1, strs2);
}

/// <summary>
/// 求笛卡尔乘积
/// </summary>
/// <param name="strs1"></param>
/// <param name="strs2"></param>
/// <returns></returns>
vector<string> Solution17::cartesian(string str1, string str2) {
    vector<string> strs1;
    for (char c : str1) {
        strs1.push_back(string(c, 1));
    }

    return cartesian(strs1, str2);
}

vector<string> Solution17::letterCombinations(string digits) {
    // 笛卡尔乘积法
    vector<string> ans;

    for (int i = 0; i < digits.length(); i++) {
        ans = cartesian(ans, (*(digitToCharTable.find(digits[i]))).second);
    }

    return ans;
}

std::vector<std::string> Solution17::letterCombinations2(std::string digits) {
    // 回溯算法

    std::vector<std::string> ans;
    if (digits.size() == 0) {
        return ans;
    }

    backtrack(ans, digits);
    return ans;
}

void Solution17::backtrack(vector<string>& ans, string digits, int depth, string currentStr) {
    if (depth >= digits.size()) {
        ans.push_back(currentStr);
    }
    else {
        for (char c : (*(digitToCharTable.find(digits[depth]))).second) {
            currentStr.push_back(c);
            backtrack(ans, digits, depth + 1, currentStr);
            currentStr.pop_back();
        }
    }
    return;
}
