#include "Solution179.h"

#include <algorithm>
#include <unordered_map>

using namespace std;

std::string Solution179::largestNumber(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end(), [](int a, int b) {
        return to_string(a) + to_string(b) > to_string(b) + to_string(a);
    });

    std::string str = "";
    for (auto num : nums) {
        str += std::to_string(num);
    }

    int p = str.find_first_not_of("0");

    if (p == string::npos) return "0";
    return str.substr(p);
}
