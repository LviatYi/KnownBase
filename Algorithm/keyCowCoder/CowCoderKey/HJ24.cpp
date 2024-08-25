#include <iostream>
#include <unordered_set>

using namespace std;

int hj24() {
    int count;
    while (cin >> count) {
        std::vector<int> nums(count);
        while (count--) {
            cin >> nums[nums.size() - count - 1];
        }

        std::vector<int> dp_l(nums.size());
        std::vector<int> dp_r(nums.size());
        dp_l[0] = 1;
        dp_r[nums.size() - 1] = 1;

        for (int i = 1; i < nums.size(); ++i) {
            int max_length = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i] && dp_l[j] + 1 > max_length) {
                    max_length = dp_l[j] + 1;
                }
            }

            dp_l[i] = max_length;
        }

        for (int i = nums.size() - 2; i >= 0; --i) {
            int max_length = 1;
            for (int j = nums.size() - 1; j > i; --j) {
                if (nums[j] < nums[i] && dp_r[j] + 1 > max_length) {
                    max_length = dp_r[j] + 1;
                }
            }

            dp_r[i] = max_length;
        }

        int max = 0;
        for (int i = 0; i < nums.size(); ++i) {
            auto val = dp_l[i] + dp_r[i] - 1;
            if (val > max) {
                max = val;
            }
        }

        std::cout << nums.size() - max << std::endl;
    }

    return 0;
}
