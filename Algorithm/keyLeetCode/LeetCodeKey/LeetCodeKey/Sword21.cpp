#include "Sword21.h"

vector<int> Sword21::exchange(vector<int>& nums) {
    vector<int>::iterator l = nums.begin();
    vector<int>::iterator r = nums.begin();

    while (r != nums.end()) {
        if (*r % 2) {
            //is odd
            int t = *l;
            *l = *r;
            *r = t;
            l++;
        }
        r++;
    }
    return nums;
}
