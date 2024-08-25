#include "Swordii60.h"

#include <set>
#include <unordered_map>

void Swordii60::qsort(std::vector<std::pair<int, int>>& v, int start, int end, std::vector<int>& ret, int k) {
    int picked = rand() % (end - start + 1) + start;
    swap(v[picked], v[start]);

    int pivot = v[start].second;
    int index = start;
    for (int i = start + 1; i <= end; i++) {
        if (v[i].second >= pivot) {
            swap(v[index + 1], v[i]);
            index++;
        }
    }
    swap(v[start], v[index]);

    if (k <= index - start) {
        qsort(v, start, index - 1, ret, k);
    }
    else {
        for (int i = start; i <= index; i++) {
            ret.push_back(v[i].first);
        }
        if (k > index - start + 1) {
            qsort(v, index + 1, end, ret, k - (index - start + 1));
        }
    }
}

std::vector<int> Swordii60::topKFrequent(std::vector<int>& nums, int k) {
    std::unordered_map<int, int> occurrences;
    for (auto& v : nums) {
        occurrences[v]++;
    }

    std::vector<std::pair<int, int>> values;
    for (auto& kv : occurrences) {
        values.push_back(kv);
    }
    std::vector<int> ret;
    qsort(values, 0, values.size() - 1, ret, k);
    return ret;
}
