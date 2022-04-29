#include "Sword61.h"
#include <algorithm>
using std::sort;

bool Sword61::isStraight(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int wildcard = 0;
        int last = 0;
        for (int num : nums) {
            if (num == 0) {
                wildcard++;
            }
            else if (last == 0 || num == last + 1 || (num != last) && (wildcard -= num - last - 1) >= 0) {
                last = num;
                continue;
            }
            else {
                return false;
            }
        }

        return true;
}
