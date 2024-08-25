#include <algorithm>

#include "Solutions.h"
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>

struct Info {
    int price;
    int value;
};

inline int get_narrow_price(int price, int ratio = 10) {
    return price / ratio;
}

/**
 *
 * @param candidate 所有候选件。
 * @param attach_map 主附件归属映射。主件归属 0，附件归属 >0。
 *  <primer_index, attach_list> 主件在 candidate 中的索引，对应附件在 candidate 中的索引。
 * @param dp 动态规划表。dp[i][j] 预算 (narrowed) 为 i 时，选取前 j 个主件的最大价值。
 * @return
 */
auto get_max_dp(const std::vector<Info*>& candidate,
                std::unordered_map<int, std::vector<int>>& attach_map,
                std::vector<std::vector<int>>& dp) {
    auto prime_candidate = attach_map.at(0);
    for (int i = 1; i < dp.size(); ++i) {
        for (int j = 1; j <= prime_candidate.size(); ++j) {
            const auto prime_item_index = prime_candidate[j - 1];
            const auto prime_item = candidate[prime_item_index];
            auto max = dp[i][j - 1];

            if (i >= get_narrow_price(prime_item->price)) {
                max = std::max(max,
                               dp[i - get_narrow_price(prime_item->price)][j - 1]
                               + prime_item->price * prime_item->value);

                if (attach_map.find(prime_item_index + 1) != attach_map.end()) {
                    const auto& list = attach_map.find(prime_item_index + 1)->second;
                    for (int m = 1; m < 1 << list.size(); ++m) {
                        auto sum = prime_item->price * prime_item->value;
                        auto money = i - get_narrow_price(prime_item->price);
                        for (int n = 0; n < list.size(); ++n) {
                            if (m & 1 << n) {
                                const auto focus = candidate[list[n]];
                                money -= get_narrow_price(focus->price);
                                if (money < 0) {
                                    break;
                                }

                                sum += focus->value * focus->price;
                            }
                        }
                        if (money >= 0) {
                            sum += dp[money][j - 1];
                            max = std::max(max, sum);
                        }
                    }
                }
            }

            dp[i][j] = max;
        }
    }
}

int hj16() {
    int budget, count;
    while (std::cin >> budget >> count) {
        auto candidate = std::vector<Info*>();
        auto primer_map = std::unordered_map<int, std::vector<int>>();
        auto dp_map = std::vector<std::vector<int>>();
        auto prime_count = 0;

        for (int i = 0; i < count; ++i) {
            int price, value, flag;
            std::cin >> price >> value >> flag;

            const auto info = new Info{price, value};
            candidate.push_back(info);
            if (flag == 0) ++prime_count;

            if (primer_map.find(flag) == primer_map.end()) {
                primer_map[flag] = std::vector<int>();
            }
            primer_map[flag].push_back(i);
        }

        for (int i = 0; i < get_narrow_price(budget) + 1; ++i) {
            dp_map.emplace_back(prime_count + 1, 0);
        }

        get_max_dp(candidate, primer_map, dp_map);

        int max = 0;
        for (auto value : dp_map[get_narrow_price(budget)]) {
            if (value > max)max = value;
        }

        std::cout << max << std::endl;

        for (auto p : candidate) {
            delete p;
        }
    }

    return 0;
}
