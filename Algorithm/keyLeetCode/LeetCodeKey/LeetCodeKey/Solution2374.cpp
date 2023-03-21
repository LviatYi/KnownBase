#include "Solution2374.h"

int Solution2374::edgeScore(std::vector<int>& edges) {
    if (edges.empty()) {
        return 0;
    }

    std::vector<int> edge_count = std::vector<int>(edges.size(), 0);
    int max_index = 0;

    for (int i = 0; i < edges.size(); ++i) {
        edge_count[edges[i]] += i;

        if (edge_count[edges[i]] > edge_count[max_index]) {
            max_index = edges[i];
        }
        else if (edge_count[edges[i]] == edge_count[max_index] && edges[i] < max_index) {
            max_index = edges[i];
        }
    }

    return max_index;
}
