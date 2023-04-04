#include "Solution875.h"

#include <algorithm>

int Solution875::minEatingSpeed(std::vector<int>& piles, int h) {
    int begin = 1;
    int end = *std::max_element(piles.begin(), piles.end());

    while (begin < end) {
        int size = (begin + end) >> 1;
        int pile_count = 0;
        for (int pile : piles) {
            pile_count += pile / size;
            pile_count += (pile % size) > 0;
            if (pile_count > h) {
                begin = size + 1;
                break;
            }
        }
        if (pile_count <= h) {
            end = size;
        }
    }

    return end;
}
