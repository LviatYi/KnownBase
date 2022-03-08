#include "Solution1.h"

#include <vector>

using namespace std;

Solution1::Solution1() {
}

Solution1::~Solution1() {
}

vector<int> Solution1::twoSum(vector<int>& nums, int target) {
    vector<int> ans;
    for (int i = 0; i < nums.size(); i++) {
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[i] + nums[j] == target) {
                ans.push_back(i);
                ans.push_back(j);
                return ans;
            }
        }
    }
    return ans;
}

std::vector<int> Solution1::twoSum2(std::vector<int>& nums, int target) {
    vector<int> ans;

    return ans;
}
