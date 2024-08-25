#include "Swordii93.h"

#include <unordered_map>

int Swordii93::lenLongestFibSubseq(std::vector<int>& arr) {
    std::unordered_map<int, int> map;
    size_t n = arr.size();
    std::vector dp(n, std::vector(n, 0));


    for (int i = 0; i < n; ++i) {
        map[arr[i]] = i;
    }

    int max = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] - arr[i] < arr[i] && map.count(arr[j] - arr[i])) {
                int current = dp[map[arr[j] - arr[i]]][i] + 1;
                max = std::max(current, max);
                dp[i][j] = current;
            }
        }
    }

    return max != 0 ? max + 2 : 0;
}
