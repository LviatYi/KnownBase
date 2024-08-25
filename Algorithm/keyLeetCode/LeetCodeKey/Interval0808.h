#pragma once
#include <string>
#include <vector>

class Interval0808 {
private :
    void dfs(std::vector<std::string>& result, std::array<int, 52>& char_table, std::string curr, int target_length);

public:
    std::vector<std::string> permutation(std::string S);
};
