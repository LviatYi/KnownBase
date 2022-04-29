#include "Sword57.h"
#include<cmath>

using std::sqrt;

vector<int> Sword57::twoSum(vector<int>& nums, int target) {
    int lPos = 0;
    int rPos = nums.size() - 1;

    while (lPos < rPos) {
        if (nums.at(lPos) == target - nums.at(rPos)) {
            return { nums.at(lPos) , nums.at(rPos) };
        }
        else if (nums.at(lPos) < target - nums.at(rPos)) {
            lPos++;
        }
        else {
            rPos--;
        }
    }

    return {};
}

vector<vector<int>> Sword57::findContinuousSequence(int target) {
    vector < vector<int>> ans;

    vector<int> currAns;
    for (int i = 1; i < target; i++) {
        long long b = (2 * i - 1);
        long long c = 2 * target;
        double delta = sqrt(b * b + 4 * c);

        if (delta == (long long)delta && ((long long)delta - b) % 2 == 0) {
            long long x = (delta - b) / 2;

            for (int j = i; j < i + x; j++) {
                currAns.push_back(j);
            }
            ans.push_back(currAns);
            currAns.clear();
        }
    }
    return ans;
}
