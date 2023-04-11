#include "Swordii87.h"
#include <format>

void Swordii87::dfs(const std::string& s, size_t start) {
    if (ip_elements_.size() == 4) {
        if (start >= s.size()) {
            ans_.push_back(composite_ip(ip_elements_));
        }
        else {
            return;
        }
    }


    for (size_t i = start + 1; i <= s.size(); ++i) {
        std::string element_str = is_valid_ip_element(s, std::next(s.begin(), start), std::next(s.begin(), i));

        if (!element_str.empty()) {
            ip_elements_.push_back(element_str);
            dfs(s, i);
            ip_elements_.pop_back();
        }
        else {
            break;
        }
    }
}

std::string Swordii87::composite_ip(std::vector<std::string>& ip_elements) {
    std::string ip = ip_elements[0] + "." + ip_elements[1] + "." + ip_elements[2] + "." + ip_elements[3];

    //std::string ip = std::format("{}.{}.{}.{}", ip_elements[0], ip_elements[1], ip_elements[2], ip_elements[3]);

    return ip;
}

std::string Swordii87::is_valid_ip_element(const std::string& s, const std::string::const_iterator& begin,
                                           const std::string::const_iterator& end) const {
    std::string str = std::string(begin, end);
    if (*begin == '0') {
        if (end == begin + 1) {
            return std::string(begin, end);
        }
        else {
            return "";
        }

    }

    int num = std::stoi(str);

    if (num < 256) {
        return str;
    }
    return "";
}

std::vector<std::string> Swordii87::restoreIpAddresses(std::string s) {
    dfs(s, 0);

    return ans_;
}
