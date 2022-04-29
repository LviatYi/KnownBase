#include "Sword45.h"
#include<algorithm>
#include<string>

using std::to_string;

string Sword45::minNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [](int lhs, int rhs) {
            string lstr = to_string(lhs);
            string rstr = to_string(rhs);

            return std::stoll(lstr + rstr) < std::stoll(rstr + lstr);
            });

        string ans;
        for (int num : nums) {
            ans += to_string(num);
        }
        return ans;
}
