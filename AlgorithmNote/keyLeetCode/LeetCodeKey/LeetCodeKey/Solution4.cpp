#include "Solution4.h"

double Solution4::findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int count = nums1.size() + nums2.size();
    int j = 0, k = 0;
    int num1 = 0, num2 = 0;
    for (int i = 0; i < count / 2 + 1; i++) {
        num2 = num1;
        num1 = k >= nums2.size() || !(j >= nums1.size()) && nums1[j] < nums2[k] ? nums1[j++] : nums2[k++];
        //if (k >= nums2.size()) {
        //    num1 = nums1[j++];
        //}
        //else  if (j >= nums1.size()) {
        //    num1 = nums2[k++];
        //}
        //else {
        //    num1 = nums1[j] < nums2[k] ? nums1[j++] : nums2[k++];
        //}
    }
    if (count % 2) {
        return
            num1;
    }
    else {
        return (num1 + num2) / 2.0;
    }
}

double Solution4::findMedianSortedArrays2(vector<int>& nums1, vector<int>& nums2) {
    if ((nums1.size() + nums2.size()) % 2) {
        return getIndexSortedArrays(nums1, nums2, (nums1.size() + nums2.size()) / 2 + 1, nums1.begin(), nums2.begin());
    }
    else {
        return
            (getIndexSortedArrays(nums1, nums2, (nums1.size() + nums2.size()) / 2, nums1.begin(), nums2.begin())
                +
                getIndexSortedArrays(nums1, nums2, (nums1.size() + nums2.size()) / 2 + 1, nums1.begin(), nums2.begin()))
            / 2.0;
    }
}

/// <summary>
/// 获取 两有序向量中 指定 index 的元素。
/// </summary>
/// <param name="nums1">向量 1 。</param>
/// <param name="nums2">向量 2 。</param>
/// <param name="index">目标元素在两个向量中的排序值。</param>
/// <param name="i1">用于指示 nums1 的起始位置，一般为 nums1.begin() 。</param>
/// <param name="i2">用于指示 nums2 的起始位置，一般为 nums2.begin() 。</param>
/// <returns></returns>
template<typename T>
T Solution4::getIndexSortedArrays(vector<T>& nums1, vector<T>& nums2, int index, typename vector<T>::iterator i1, typename vector<T>::iterator i2) {
    if (i1 >= nums1.end()) {
        return *(i2 + index - 1);
    }
    if (i2 >= nums2.end()) {
        return *(i1 + index - 1);
    }

    if (index == 1) {
        return *i1 < *i2 ? *i1 : *i2;
    }

    int key = index / 2 - 1;

    // 二分排除掉的元素数量。
    int count;

    if (*(i1 + key < nums1.end() ? i1 + key : nums1.end() - 1) < *(i2 + key < nums2.end() ? i2 + key : nums2.end() - 1)) {
        count = i1 + key < nums1.end() ? 1 + key : nums1.size();
        return getIndexSortedArrays(nums1, nums2, index - count, i1 + count, i2);
    }
    else {
        count = i2 + key < nums2.end() ? 1 + key : nums2.size();
        return getIndexSortedArrays(nums1, nums2, index - count, i1, i2 + count);
    }
}



