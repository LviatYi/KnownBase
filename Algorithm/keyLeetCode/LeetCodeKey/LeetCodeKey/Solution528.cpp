#include "Solution528.h"

Solution528::Solution528(std::vector<int>& w) {
    int sum = 0;

    for (const int weight : w) {
        sum += weight;
        _w_sum.push_back(sum);
    }

}

int Solution528::pickIndex() {
    if (_w_sum.empty()) {
        return -1;
    }

    int rand_target = rand() % _w_sum.back();

    return std::upper_bound(_w_sum.begin(), _w_sum.end(), rand_target) - _w_sum.begin();
}
