#include "Sword51.h"
#include<stack>
using std::stack;

#pragma region 归并排序_using_vector
// 相较于 array ，vector 的 push_back 的动态性使其效率大打折扣。
// 构造 vector 也有损耗。
static int mergeSort(vector<int>& nums, vector<int>& temp, int begin, int end) {
    if (begin > end - 1) {
        return 0;
    }
    else if (begin == end - 1) {
        temp.at(begin) = nums.at(begin);
        return 0;
    }

    int mid = (begin + end) / 2;
    int ans = mergeSort(nums, temp, begin, mid) + mergeSort(nums, temp, mid, end);

    int l = begin;
    int r = mid;
    int i = 0;
    // 提前指定其长度 可大幅增加性能。
    vector<int> t(end - begin);

    while (l != mid && r != end) {
        if (temp[l] <= temp[r]) {
            t[i++] = temp[l++];
        }
        else {
            ans += mid - l;
            t[i++] = temp[r++];
        }
    }
    while (l != mid) {
        t[i++] = temp[l++];
    }
    while (r != end) {
        t[i++] = temp[r++];
    }

    copy(t.begin(), t.end(), temp.begin() + begin);
    return ans;
}

int Sword51::reversePairs(vector<int>& nums) {
    vector<int>temp(nums.size());
    return mergeSort(nums, temp, 0, nums.size());
}
#pragma endregion
#pragma region 归并排序_using_array
// 大幅提高运行效率

#include<array>
using std::array;
static int mergeSort2(vector<int>& nums, vector<int>& temp, int begin, int end, int* t) {
    if (begin > end - 1) {
        return 0;
    }
    else if (begin == end - 1) {
        temp.at(begin) = nums.at(begin);
        return 0;
    }

    int mid = (begin + end) / 2;
    int ans = mergeSort2(nums, temp, begin, mid, t) + mergeSort2(nums, temp, mid, end, t);

    int l = begin;
    int r = mid;
    int i = begin;

    while (l != mid && r != end) {
        if (temp[l] <= temp[r]) {
            t[i++] = temp[l++];
        }
        else {
            ans += mid - l;
            t[i++] = temp[r++];
        }
    }
    while (l != mid) {
        t[i++] = temp[l++];
    }
    while (r != end) {
        t[i++] = temp[r++];
    }

    copy(t + begin, t + end, temp.begin() + begin);
    return ans;
}

int Sword51::reversePairs2(vector<int>& nums) {
    int* t = new int[nums.size()];
    vector<int>temp(nums.size());
    return mergeSort2(nums, temp, 0, nums.size(), t);
    delete[]t;
}
#pragma endregion