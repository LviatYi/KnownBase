#include "Main.h"
#include "Solutions.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    Solution4 solution;
    vector<int> nums1 = { 1,2 };
    vector<int> nums2 = { 3,4 };


    double i = solution.findMedianSortedArrays2(nums1, nums2);

    cout << i;

    return 1;
}
