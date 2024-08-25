#pragma once
#include <string>
#include <vector>

class Solution93 {
private:
    std::vector<std::string> ip_elements_;
    std::vector<std::string> ans_;

    void dfs(const std::string& s, size_t start);

    std::string is_valid_ip_element(const std::string& s, const std::string::const_iterator& begin,
                                    const std::string::const_iterator& end) const;
    std::string composite_ip(std::vector<std::string>& ip_elements);
public:
    std::vector<std::string> restoreIpAddresses(std::string s);
};
