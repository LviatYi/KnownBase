#include "Solution924.h"

#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int Solution924::minMalwareSpread(std::vector<std::vector<int>>& graph,
                                  std::vector<int>& initial) {
    int n = graph.size();
    std::vector<int> visited(n);
    std::unordered_map<int, int> id_to_size;
    int id = 0;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            ++id;
            int size = 1;
            queue<int> q;
            q.push(i);
            visited[i] = id;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v = 0; v < n; ++v) {
                    if (!visited[v] && graph[u][v] == 1) {
                        ++size;
                        q.push(v);
                        visited[v] = id;
                    }
                }
            }
            id_to_size[id] = size;
        }
    }
    std::unordered_map<int, int> id_to_initials;
    for (int u : initial) {
        ++id_to_initials[visited[u]];
    }
    int ans = n + 1, ans_removed = 0;
    for (int u : initial) {
        int removed = (id_to_initials[visited[u]] == 1 ? id_to_size[visited[u]] : 0);
        if (removed > ans_removed || (removed == ans_removed && u < ans)) {
            ans = u;
            ans_removed = removed;
        }
    }
    return ans;
}
