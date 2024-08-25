#include "Swordii6.h"

vector<int> Swordii6::twoSum(vector<int>& numbers, int target) {
    int left = 0, right = numbers.size() - 1;
    int curr_sum = numbers.at(left) + numbers.at(right);
    while (curr_sum != target) {
        if (curr_sum < target) {
            left++;
        }
        else {
            right--;
        }
        curr_sum = numbers.at(left) + numbers.at(right);
    }

    return {left, right};
}
