#include "Solution354.h"

#include <algorithm>
#include <execution>

int Solution354::maxEnvelopes(std::vector<std::vector<int>>& envelopes) {
    std::sort(envelopes.begin(),
              envelopes.end(),
              [](const std::vector<int>& a, const std::vector<int>& b) {
                  return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
              });

    // std::vector<std::pair<std::pair<int, int>, int>> dp(envelopes.size());
    std::vector<int> data_list(envelopes.size());
    for (int i = 0; i < envelopes.size(); ++i) {
        data_list[i] = envelopes[i][1];
    }
    // std::vector<int> dp(envelopes.size(), 1);
    //
    // int max = 1;
    // for (int i = 1; i < envelopes.size(); ++i) {
    //     for (int r = i - 1; r >= 0; --r) {
    //         if (data_list[r] < data_list[i]) {
    //             dp[i] = std::max(dp[i], dp[r] + 1);
    //         }
    //     }
    //
    //     if (max < dp[i])max = dp[i];
    // }

    std::vector<int> card;
    for (int i = 0; i < data_list.size(); ++i) {
        const auto num = data_list[i];
        bool inserted = false;
        auto it = std::lower_bound(card.begin(), card.end(), num);
        if (it != card.end()) {
            *it = num;
            inserted = true;
        } else {
            card.push_back(num);
        }
    }


    return card.size();
}
