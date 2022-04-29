#include "Sword11.h"

int Sword11::minArray(vector<int>& numbers) {
    int begin = 0;
    int end = numbers.size() - 1;
    // 避免溢出
    int mid = begin + (end - begin) / 2;

    while (mid < end) {
        if (numbers[mid] > numbers[end]) {
            begin = mid + 1;
        }
        else if (numbers[mid] < numbers[end]) {
            end = mid;
        }
        else {
            end--;
        }

        mid = (begin + end) / 2;

    }

    return numbers[0] < numbers[end] ? numbers[0] : numbers[end];
}
