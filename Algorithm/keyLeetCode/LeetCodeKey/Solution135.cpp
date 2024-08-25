#include "Solution135.h"
#include <unordered_map>

using namespace std;

int Solution135::candy(std::vector<int>& ratings) {
    auto vals = std::vector<int>(ratings.size(), 1);
    for (int i = 1; i < ratings.size(); ++i) {
        if (ratings[i] > ratings[i - 1]) {
            vals[i] = vals[i - 1] + 1;
        }
    }

    int sum = vals[ratings.size() - 1];
    for (int i = ratings.size() - 2; i >= 0; --i) {
        if (ratings[i] > ratings[i + 1]) {
            vals[i] = std::max(vals[i + 1] + 1, vals[i]);
            sum += vals[i];
        } else {
            sum += vals[i];
        }
    }

    return sum;
}
