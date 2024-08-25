#include "Sword63.h"
#include <algorithm>

using std::max;
using std::min;

#pragma region 二分查找
struct profitBinInfo {
    int max;
    int min;
    int profit;

    profitBinInfo() = default;

    profitBinInfo(int max, int min, int profit)
        : max(max),
        min(min),
        profit(profit) {
    }
};

static profitBinInfo maxSubProfit(vector<int>& prices, int begin, int end) {
    if (begin >= end) {
        return { 0,0,0 };
    }
    if (begin == end - 1) {
        return { prices[begin], prices[begin], 0 };
    }

    int mid = (begin + end) / 2;

    profitBinInfo left = maxSubProfit(prices, begin, mid);
    profitBinInfo right = maxSubProfit(prices, mid, end);

    return { max(left.max, right.max), min(left.min, right.min), max({left.profit, right.profit, right.max - left.min,0 }) };
}

int Sword63::maxProfit(vector<int>& prices) {
    return maxSubProfit(prices, 0, static_cast<int>(prices.size())).profit;
}
#pragma endregion
#pragma region 一次遍历
int Sword63::maxProfit2(vector<int>& prices) {
    int maxProfit = 0;
    int lowest = INT_MAX;
    for (int p : prices) {
        maxProfit = max(p - lowest, maxProfit);
        lowest = min(p, lowest);
    }
    return maxProfit;
}
#pragma endregion


