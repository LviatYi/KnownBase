#include "Solution421.h"

void Solution421::Character_dict::insert(int val, int index) {
    if (index < 0) {
        return;
    }

    int i = 1 << index;
    if (i & val) {
        if (chars[1] == nullptr) {
            chars[1] = new Character_dict;
        }
        chars[1]->insert(val, index - 1);

    }
    else {
        if (chars[0] == nullptr) {
            chars[0] = new Character_dict;
        }
        chars[0]->insert(val, index - 1);
    }
}

int Solution421::findMaximumXOR(std::vector<int>& nums) {
    int max_sum = 0;
    for (int num : nums) {
        int sum = 0;

        auto current = dict_;
        int i = 31;

        while (i >= 0) {
            if (!current->chars[0] && !current->chars[1]) {
                break;
            }

            if (current->chars[!(1 << i & num)]) {
                current = current->chars[!(1 << i & num)];
                sum += 1 << i;
            }
            else {
                current = current->chars[static_cast<bool>(1 << i & num)];
            }

            --i;
        }

        max_sum = std::max(max_sum, sum);

        dict_->insert(num);
    }

    return max_sum;
}
