#include "Solution34.h"

using namespace std;

std::vector<int> Solution34::searchRange(std::vector<int>& nums, int target) {
    vector<int>ans;
    if (nums.size() == 0) {
        ans.push_back(-1);
        ans.push_back(-1);
        return ans;
    }

    int start = 0;
    int end = nums.size() - 1;
    int mid = (start + end) / 2;

    while (start < end) {
        if (nums[mid] > target) {
            end = mid - 1;
        }
        else if (nums[mid] < target) {
            start = mid + 1;
        }
        else {
            int lEnd = mid;
            int rStart = mid;

            mid = (start + lEnd) / 2;

            while (nums[start] < target) {
                if (nums[mid] < target) {
                    start = mid + 1;
                }
                else {
                    lEnd = mid - 1;
                }
                mid = (start + lEnd) / 2;
            }

            mid = (rStart + end) / 2;

            while (nums[end] > target) {
                if (nums[mid] > target) {
                    end = mid - 1;
                }
                else {
                    rStart = mid + 1;
                }
                mid = (rStart + end) / 2;
            }

            break;
        }
        mid = (start + end) / 2;
    }

    ans.push_back(start < nums.size() && nums[start] == target ? start : -1);
    ans.push_back(end >= 0 && nums[end] == target ? end : -1);

    return ans;
}
