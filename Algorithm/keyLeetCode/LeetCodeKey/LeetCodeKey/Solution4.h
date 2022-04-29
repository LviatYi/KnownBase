#pragma once
#include<vector>

using namespace std;

class Solution4 {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2);
    double findMedianSortedArrays2(vector<int>& nums1, vector<int>& nums2);

    template<typename T>
    T getIndexSortedArrays(vector<T>& nums1, vector<T>& nums2, int index, typename vector<T>::iterator i1, typename  vector<T>::iterator i2);
};

