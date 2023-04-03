#include "Swordii69.h"

int Swordii69::peakIndexInMountainArray(std::vector<int>& arr) {
    if (arr.empty()) {
        return 0;
    }

    size_t start = 0;
    size_t end = arr.size();
    while (start < end) {
        size_t i = (start + end) / 2;
        if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
            return static_cast<int>(i);
        }


        if (arr[i] < arr[i + 1]) {
            start = i + 1;
        }
        else {
            end = i;
        }
    }

    return -1;
}
