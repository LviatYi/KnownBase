#pragma once
#include <string>
#include <vector>

class Swordii85 {
private:
    std::string temp;
    std::vector<std::string> ret;
    void dfs(const int& n, int pre_count, int back_count);
public:
    std::vector<std::string> generateParenthesis(int n);

};
