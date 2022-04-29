#pragma once
#include <vector>
#include <string>
#include <unordered_map>

class Solution17 {
private:
    std::unordered_map<char, std::string> digitToCharTable{
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}
    };
    std::vector<std::string> cartesian(std::vector<std::string> strs1, std::vector<std::string> strs2);
    std::vector<std::string> cartesian(std::vector<std::string> strs1, std::string str2);
    std::vector<std::string> cartesian(std::string strs1, std::string strs2);
    void backtrack(std::vector<std::string>& ans, std::string digits, int depth = 0, std::string currentStr = "");
public:
    std::vector<std::string> letterCombinations(std::string digits);
    std::vector<std::string> letterCombinations2(std::string digits);
};
