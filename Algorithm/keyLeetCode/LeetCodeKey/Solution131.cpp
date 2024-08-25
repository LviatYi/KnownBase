#include "Solution131.h"

void Solution131::dfs(std::string& s, size_t start) {
    if (start >= s.size()) {
        ans_.push_back(temp_);
        return;
    }

    for (size_t i = start; i < s.size(); ++i) {
        if (dp_[start][i]) {
            temp_.push_back(s.substr(start, i - start + 1));
            dfs(s, i + 1);
            temp_.pop_back();
        }
    }
}

std::vector<std::vector<std::string>> Solution131::partition(std::string s) {
    size_t n = s.size();
    dp_.assign(n, std::vector<bool>(n, true));

    for (size_t j = 1; j < n; ++j) {
        for (size_t i = 0; i < j; ++i) {
            dp_[i][j] = dp_[i + 1][j - 1] && s[i] == s[j];
        }
    }

    dfs(s, 0);

    return ans_;
}
