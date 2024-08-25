#pragma once
#include <string>
#include <vector>

class Swordii86 {
private:
    std::vector<std::vector<bool>> dp_;
    std::vector<std::string> temp_;
    std::vector<std::vector<std::string>> ans_;

    void dfs(std::string& s, size_t start);

public:
    std::vector<std::vector<std::string>> partition(std::string s);
};
