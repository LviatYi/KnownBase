#include "Sword3.h"
#include<unordered_set>

using std::unordered_set;

int Sword3::findRepeatNumber(vector<int>& nums) {
    unordered_set<int> set;
    for (int num : nums) {
        if (!set.insert(num).second) {
            return num;
        }
    }

    return 0;
}
