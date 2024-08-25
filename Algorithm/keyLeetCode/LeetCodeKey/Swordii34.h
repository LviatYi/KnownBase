#pragma once
#include <string>
#include <vector>

class Swordii34 {
private:
    int compare(char table[], std::string& lhs, std::string& rhs);
    int compare(char table[], char& lhs, char& rhs);

public:
    bool isAlienSorted(std::vector<std::string>& words, std::string order);
};
