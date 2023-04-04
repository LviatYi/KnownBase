#include "Swordii71.h"

#include <ctime>
#include <iterator>
#include <numeric>

Swordii71::Swordii71(std::vector<int>& w) {
    //int sum = 0;

    //for (const int weight : w) {
    //    sum += weight;
    //    _w_sum.push_back(sum);
    //}

    // 前缀和计算                                                 后插入迭代器
    std::partial_sum(w.begin(), w.end(), back_inserter(_w_sum));
}

int Swordii71::pickIndex() {
    if (_w_sum.empty()) {
        return -1;
    }

    srand(static_cast<unsigned>(clock()));
    int rand_target = rand() % _w_sum.back();

    return std::upper_bound(_w_sum.begin(), _w_sum.end(), rand_target) - _w_sum.begin();
}
