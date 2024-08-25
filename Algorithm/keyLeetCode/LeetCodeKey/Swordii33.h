#pragma once
#include <string>
#include <vector>

class Swordii33 {
public:
    class Anagram {
    public:
        Anagram(const std::string& str);
        friend bool operator==(const Anagram& lhs, const Anagram& rhs);
        int feature_[26]{0};
    };

    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs);
    std::vector<std::vector<std::string>> groupAnagrams2(std::vector<std::string>& strs);
};
