#include "Solution1122.h"

#include <algorithm>

std::vector<int> Solution1122::relativeSortArray(std::vector<int>& arr1, std::vector<int>& arr2) {
    const int size = 1001;
    int map[size];
    std::fill(std::begin(map), std::end(map), INT_MAX);

    for (int i = 0; i < arr2.size(); ++i) {
        map[arr2[i]] = i;
    }

    std::sort(arr1.begin(), arr1.end(), [map](const int lhs, const int rhs)-> bool {
        const int val_lhs = map[lhs];
        const int val_rhs = map[rhs];

        return val_lhs == INT_MAX && val_rhs == INT_MAX ? lhs < rhs : val_lhs < val_rhs;
    });

    return arr1;
}
